#include "Control.h"
#include <crtdbg.h>
#include <cmath>
#include "Test.h"


int main(void) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(5082583);

	//TODO ‚±‚ê‚ªmain
	Control control = Control();
	control.start();

	system("pause > 0");

	return 0;
}


