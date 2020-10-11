#include "injector.hpp"

bool injector::perform_inject(
    const uint32_t process_id,
    const std::string_view dll_path,
    bool elevate_handle
)
{
    HANDLE process_handle;

    //
    // open process handle
    //
    if (elevate_handle)
    {
        //
        // open the handle with lowest privileage
        // in order to elevate
        //
        process_handle = OpenProcess(
            PROCESS_QUERY_LIMITED_INFORMATION,
            FALSE,
            process_id
        );

        RET_CHECK(grant_access(process_handle, PROCESS_ALL_ACCESS));
    }
    else
    {
        //
        // open the handle normally
        // this might not be work for protected processes
        //
        process_handle = OpenProcess(
            PROCESS_ALL_ACCESS,
            FALSE,
            process_id
        );
    }

    RET_CHECK(CHECK_HANDLE(process_handle));

    //
    // allocate memory in target process
    //
    void* allocated_memory = memory::allocate(
        process_handle,
        NULL,
        dll_path.size(),
        MEM_COMMIT,
        PAGE_READWRITE
    );

    RET_CHECK(allocated_memory);

    //
    // write dll in allocated memory
    //
    RET_CHECK(memory::write_raw(
        process_handle,
        (uint64_t)allocated_memory,
        (void*)dll_path.data(),
        dll_path.size()
    ));

    //
    // find function address of LoadLibrary
    // this address is static but different between 32bit and 64bit
    //
    void* function_address = GetProcAddress(
        GetModuleHandle(TEXT("Kernel32.dll")),  // module to find
        "LoadLibraryA"                          // procedure name
    );

    RET_CHECK(function_address);

    //
    // create thread remotely in target process
    // and let thread call the LoadLibrary with the augment of dll path.
    //
    HANDLE thread_handle = CreateRemoteThread(
        process_handle,                             // process handle
        NULL,                                       // thread attributes
        0,                                          // stack size
        (LPTHREAD_START_ROUTINE)function_address,   // start address
        allocated_memory,                           // parameter
        0,                                          // creation flags
        NULL                                        // thread id
    );

    RET_CHECK(CHECK_HANDLE(thread_handle));

    return true;
}
