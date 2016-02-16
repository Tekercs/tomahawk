#include "src/core/core.h"

int main ()
{
	server().setPortNumber(9099)
            .setResourceFolderPath("./resources")
            .start();

	return 0;
}