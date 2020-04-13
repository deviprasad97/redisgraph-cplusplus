//
// Created by devi on 1/5/20.
//

#ifndef REDISGRAPHCLINET_RESULTSETSCALARTYPES_H
#define REDISGRAPHCLINET_RESULTSETSCALARTYPES_H


class ResultSetScalarTypes {
    public:
        enum ResultSetScalarTypesEnum
        {
            VALUE_UNKNOWN,
            VALUE_NULL,
            VALUE_STRING,
            VALUE_INTEGER,
            VALUE_BOOLEAN,
            VALUE_DOUBLE,
            VALUE_ARRAY,
            VALUE_EDGE,
            VALUE_NODE,
            VALUE_PATH
        };
        //static ResultSetScalarTypesEnum values[10];
        static ResultSetScalarTypesEnum getValues(int index){
            return (ResultSetScalarTypesEnum)index;
        };

};


#endif //REDISGRAPHCLINET_RESULTSETSCALARTYPES_H
