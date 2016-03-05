#include <core/Server.h>

int main ()
{
    Core::server().setPortNumber(9099)
                  .setResourceFolderPath("./resources")
                  .start();

	return 0;
}