#include "System.h"
#include "uCUnit-v1.0.h"
#include "tests.h"

int main(void)
{
    UCUNIT_Init();
    UCUNIT_WriteString("\n**************************************\n\n");
    Testsuite__list_h();
    UCUNIT_Shutdown();

    return 0;
}
