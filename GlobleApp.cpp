#include "GlobleApp.h"

GlobleApp::GlobleApp() {

}

void GlobleApp::init()
{
    threadSqlite = new ThreadSqlite();
    threadSqlite->open("test.db","test1");
}
