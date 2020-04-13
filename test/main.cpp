//
// Created by devi on 1/7/20.
//

#include "main.h"
RedisGraph api = RedisGraph("localhost", 6379);
int main()
{


    testDeletegraph();
    testCreateNode();
    testCreateLabledNode();
    testConnectNodes();
    testDeleteNodes();
    testDeleteRelationship();
    testIndex();
    testHeader();
    testRecord();
    testArraySupport();

}
void testArraySupport()
{
    api.
}
