#include "header.h"
#include "App.h"

int main()
{
	srand(int(time(NULL)));
	App app;
	app.loop();
	return 0;
}