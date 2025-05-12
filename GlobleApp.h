#ifndef GLOBLEAPP_H
#define GLOBLEAPP_H
#include "threaddblib/ThreadSqlite.h"

class GlobleApp
{
private:
    GlobleApp();
public:
    static GlobleApp& getInstance() {
        static GlobleApp instance;
        return instance;
    }
    void init();
    ThreadSqlite *threadSqlite;
};
#endif // GLOBLEAPP_H
