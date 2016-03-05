#include <core/Server.h>

int main ()
{
    Core::server().setPortNumber(9000)
                  .setResourceFolderPath("./resources")
                  .start();

	return 0;
}