#include <iostream>
#include <hiredis/hiredis.h>
#include "impl/api/RedisGraph.h"

//#define TEST_EXP
#define TEST_API
// Helper function to deflat the redisReply
void flattenList(redisReply *head)
{
    /*Base case*/
    if (head == NULL)
        return;

    redisReply *tmp;

    /* Find tail node of first level linked list */
    redisReply *tail = head->element[head->elements-1];
//    while (tail->element != NULL)
//        tail = tail->element;

    // One by one traverse through all nodes of first level
    // linked list till we reach the tail node
    redisReply *cur = head;
    while (cur != tail)
    {
        // If current node has a child
        if (cur->element)
        {
            // then append the child at the end of current list
            tail->element = cur->element;

            // and update the tail to new last node
            tmp = cur->element[0];
            while (tmp->next)
                tmp = tmp->next;
            tail = tmp;
        }

        // Change current node
        cur = cur->next;
    }
}

// Helper function to process redisReply to a vector
void print_data(redisReply *reply, std::vector<std::string> &data)
{
    if(reply->element == nullptr)
    {
        std::string data_string;
        if(reply->type == REDIS_REPLY_INTEGER){
            data_string = std::to_string(reply->integer);
        }
        else{
            data_string = reply->str;
        }
        std::cout<<data_string<<"\n";
        data.push_back(data_string);

    }
    for(int i=0; i<reply->elements; i++){
        print_data(reply->element[i], data);
    }
}


void test_implementation()
{
    unsigned int j, isunix = 0;
    redisContext *c;
    redisReply *reply;
    redisReader *reader;
    reader = redisReaderCreate();
    std::vector<std::string> data;

    const char *hostname = "127.0.0.1";
    int port = 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
// CREATE (:person {name:'Pam', age:27})-[:works {since: 2010}]->(:employer {name:'Dunder Mifflin'})
    /* GRAPH server */
    // "MATCH (n1)-[r]->(n2) RETURN n1, r, n2.name"
    // "CREATE (:Rider {name:'Valentino Rossi'})-[:rides]->(:Team {name:'Yamaha'}), (:Rider {name:'Dani Pedrosa'})-[:rides]->(:Team {name:'Honda'}), (:Rider {name:'Andrea Dovizioso'})-[:rides]->(:Team {name:'Ducati'})"

    /**
     * 1) 1) "n1"
   2) "r"
   3) "n2"
2) 1) 1) 1) 1) "id"
            2) (integer) 0
         2) 1) "labels"
            2) 1) "person"
         3) 1) "properties"
            2) 1) 1) "name"
                  2) "Pam"
               2) 1) "age"
                  2) (integer) 27
      2) 1) 1) "id"
            2) (integer) 0
         2) 1) "type"
            2) "works"
         3) 1) "src_node"
            2) (integer) 0
         4) 1) "dest_node"
            2) (integer) 1
         5) 1) "properties"
            2) 1) 1) "since"
                  2) (integer) 2010
      3) 1) 1) "id"
            2) (integer) 1
         2) 1) "labels"
            2) 1) "employer"
         3) 1) "properties"
            2) 1) 1) "name"
                  2) "Dunder Mifflin"
3) 1) "Query internal execution time: 1.476144 milliseconds"

     */

     printf("GRAPH.QUERY %s %s", "Test", "MATCH (n1)-[r]->(n2) RETURN n1, r, n2");
    reply = (redisReply *)redisCommand(c,"GRAPH.QUERY %s %s %s", "Test", "MATCH (n1)-[r]->(n2) RETURN n1, r, n2", "--compact");

    //redisReaderGetReply(reinterpret_cast<redisReader *>(redisReaderCreate), reinterpret_cast<void **>(reply));
    redisReply **resultSet = reply->element;
    redisReply* temp;

    std::vector<redisReply*> stack;
    std::set<redisReply*> visited;
    print_data(reply, data);
//    flattenList(reply);
//    int num_elements;
//    temp = reply;
//    num_elements = reply->elements;
//    for(int i=0; i<num_elements; i++)
//    {
//        stack.push_back(temp->element[i]);
//    }
//
//     while(true)
//     {
//         if(stack.empty()){
//             break;
//         }
//         temp = stack[stack.size()-1];
//         num_elements = temp->elements;
//         for(int i=0; i<=num_elements; i++)
//         {
//             if(temp->element != nullptr)
//             {
//                 stack.push_back(temp->element[i]);
//                 temp = stack[stack.size()-1];
//                 num_elements = temp->elements;
//             } else{
//                 stack.pop_back();
//                 visited.insert(temp);
//                 break;
//             }
//
//         }
//     }
    //int num_elements = resultSet->elements;
    printf("GRAPH: %s\n", reply->str);
    freeReplyObject(reply);

    // SET Method
    reply = (redisReply*)redisCommand(c,"SET foo hello");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    // GET
    reply = (redisReply*)redisCommand(c,"GET foo");
    printf("GET foo: %s\n", reply->str);
    freeReplyObject(reply);


    reply = (redisReply*)redisCommand(c,"PING %s", "Hello World");
    printf("RESPONSE: %s\n", reply->str);
    printf("error: %s\n", c->errstr);
    freeReplyObject(reply);

    /* Disconnects and frees the context */
    redisFree(c);

}

void test_api()
{
    RedisGraph redisGraph;
    redisGraph.set_graph("Test");
    redisGraph.query("MATCH (n1)-[r]->(n2) RETURN n1, r, n2");
    std::vector<std::string> raw_data = redisGraph.get_raw_data();
    ResultSet resultSet = redisGraph.getResultSet();
    std::cout<<"Done\n";
}
int main(int argc, char **argv) {
#ifdef TEST_EXP
    test_implementation();
#endif
#ifdef TEST_API
    test_api();
#endif
    return 0;
}
