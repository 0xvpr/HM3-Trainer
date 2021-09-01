/**
 * @Author: Malik R. Booker
 * @Created: August 22, 2021
 * @Modified: August 22, 2021
 *
 * @Description: Injects DLL file into target process
 *
*/
#include "injector.h"

static const char* target_process = "HitmanBloodMoney.exe";
static const char* dll_path = "./hm3_trainer.dll";

int main(void)
{
    // Acquire process id
    DWORD process_id = 0;

	printf("Searching for Hitman Blood Money...\n\n");
	while (!process_id)
		process_id = GetProcessIdByProcessName(target_process);

    // Injection
    int inject_status = InjectDLL(process_id, dll_path);
    if (inject_status != EXIT_SUCCESS)
        __handle_error(inject_status);

	// Handle errors
    printf("Injection: %s.\n", (inject_status ? "Failed" : "Successful"));
	printf("Press enter to exit...\n");
	getchar();

    return inject_status;
}
