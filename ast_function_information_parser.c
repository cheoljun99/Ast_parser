#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_c.c"
void if_finder_reculsively_iffalse(json_value path, int *counter);
void if_finder_reculsively_iftrue(json_value path, int *counter);
typedef struct Parameter
{
    char parameter_name[100];
    char parameter_return_type[100];

} Parameter;

typedef struct Func_data
{
    char func_name[100];
    char func_return_type[100];
    int parameter_count;
    Parameter **parameter_address;
    int func_using_if_count;

} Func_data;

void if_finder_reculsively_iffalse(json_value path, int *counter)
{
    // json_print(path);

    json_value path_below_iffalse = json_get_from_json_value(path, "iffalse");
    json_value path_below_iftrue = json_get_from_json_value(path, "iftrue");

    if (json_is_null(path_below_iffalse) != 1)
    {
        char *path_below_iffalse_below_node_type_checker = json_get_string(path_below_iffalse, "_nodetype");
        if (strcmp(path_below_iffalse_below_node_type_checker, "If") == 0)
        {
            // printf("if counter 증가 \n");
            (*counter)++;
            if_finder_reculsively_iffalse(path_below_iffalse, counter);
        }
        else
        {
            json_value path_below_iffalse_below_stmt = json_get_from_json_value(path_below_iffalse, "stmt");

            if (json_get_type(path_below_iffalse_below_stmt) != JSON_UNDEFINED)
            {
                if_finder_reculsively_iftrue(path_below_iffalse_below_stmt, counter);
            }
            else
            {
                return;
            }
        }
    }
    if (json_is_null(path_below_iftrue) != 1)
    {
        // printf("dfdsf");

        if_finder_reculsively_iftrue(path_below_iftrue, counter);
    }
}
void if_finder_reculsively_iftrue(json_value path, int *counter)
{
    json_value path_block_items = json_get_from_json_value(path, "block_items");

    if (path_block_items.type == JSON_ARRAY)
    {

        json_array *path_block_items_array = (json_array *)path_block_items.value;
        // printf("%d\n",path_block_items_array->last_index);
        for (int i = 0; i <= path_block_items_array->last_index; i++)
        {

            if (path_block_items_array->values[i].type == JSON_OBJECT)
            {
                char *path_block_items_array_below_node_type_checker = json_get_string(path_block_items_array->values[i], "_nodetype");
                if (strcmp(path_block_items_array_below_node_type_checker, "If") == 0)
                {
                    // printf("if counter 증가 \n");
                    (*counter)++;
                    json_value path_block_items_below_iffalse = json_get_from_json_value(path_block_items_array->values[i], "iffalse");
                    json_value path_block_items_below_iftrue = json_get_from_json_value(path_block_items_array->values[i], "iftrue");

                    if (json_is_null(path_block_items_below_iffalse) != 1)
                    {
                        char *path_block_items_below_iffalse_below_node_type_checker = json_get_string(path_block_items_below_iffalse, "_nodetype");
                        if (strcmp(path_block_items_below_iffalse_below_node_type_checker, "If") == 0)
                        {
                            // printf("if counter 증가 \n");
                            (*counter)++;
                            if_finder_reculsively_iffalse(path_block_items_below_iffalse, counter);
                        }
                        else
                        {
                            json_value path_block_items_below_iffalse_below_stmt = json_get_from_json_value(path_block_items_below_iffalse, "stmt");

                            if (json_get_type(path_block_items_below_iffalse_below_stmt) != JSON_UNDEFINED)
                            {
                                if_finder_reculsively_iftrue(path_block_items_below_iffalse_below_stmt, counter);
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    if (json_is_null(path_block_items_below_iftrue) != 1)
                    {
                        // printf("dfdsf");

                        if_finder_reculsively_iftrue(path_block_items_below_iftrue, counter);
                    }
                }
                else
                {
                    // printf("if c1111111111111 증가 \n");

                    json_value path_block_items_array_below_stmt = json_get_from_json_value(path_block_items_array->values[i], "stmt");

                    if (json_get_type(path_block_items_array_below_stmt) != JSON_UNDEFINED)
                    {

                        if_finder_reculsively_iftrue(path_block_items_array_below_stmt, counter);
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    else
    {
        // printf("if dfadfa 증가 \n");
        // json_print(path);
        char *path_node_type_checker = json_get_string(path, "_nodetype");
        if (strcmp(path_node_type_checker, "If") == 0)
        {
            // printf("if counter 증가 \n");
            (*counter)++;
            json_value path_below_iffalse = json_get_from_json_value(path, "iffalse");
            json_value path_below_iftrue = json_get_from_json_value(path, "iftrue");

            if (json_is_null(path_below_iffalse) != 1)
            {
                char *path_below_iffalse_below_node_type_checker = json_get_string(path_below_iffalse, "_nodetype");
                if (strcmp(path_below_iffalse_below_node_type_checker, "If") == 0)
                {
                    // printf("if counter 증가 \n");
                    (*counter)++;
                    if_finder_reculsively_iffalse(path_below_iffalse, counter);
                }
                else
                {
                    json_value path_below_iffalse_below_stmt = json_get_from_json_value(path_below_iffalse, "stmt");

                    if (json_get_type(path_below_iffalse_below_stmt) != JSON_UNDEFINED)
                    {
                        if_finder_reculsively_iftrue(path_below_iffalse_below_stmt, counter);
                    }
                    else
                    {
                        return;
                    }
                }
            }
            if (json_is_null(path_below_iftrue) != 1)
            {
                if_finder_reculsively_iftrue(path_below_iftrue, counter);
            }
        }
        else
        {
            json_value path_below_stmt = json_get_from_json_value(path, "stmt");
            if (json_get_type(path_below_stmt) != JSON_UNDEFINED)
            {
                if_finder_reculsively_iftrue(path_below_stmt, counter);
            }
            else
            {
                return;
            }
        }
    }
}

void load_data(json_value datas)
{
    int func_counter = 0;
    int size = json_len(datas); // 배열의 길이를 가져옵니다.
    for (int i = 0; i < size; i++)
    {
        json_value obj = json_get(datas, i);
        // json_print(obj);
        char *type = json_get_string(obj, "_nodetype");

        if (strcmp(type, "FuncDef") == 0)
        {
            func_counter++;
        }
    }
    // printf("사용된 함수의 총 개수 : %d\n", func_counter);
    Func_data *func_datas = (Func_data *)malloc(sizeof(Func_data) * func_counter);
    Parameter **parameters = (Parameter **)malloc(func_counter * sizeof(Parameter *));
    if (parameters == NULL)
    {
        printf("Memory allocation failed for rows\n");
        return;
    }

    // printf("각각의 함수 정보 뽑아내는 과정\n");
    // printf("--------------------------------------------\n");
    int struct_counter = 0;
    for (int i = 0; i < size; i++)
    {
        json_value obj = json_get(datas, i);
        // json_print(obj);
        char *type = json_get_string(obj, "_nodetype");
        if (strcmp(type, "FuncDef") == 0)
        {
            // printf("%d 번째 함수 이름 추출 \n", struct_counter + 1);
            json_value decl = json_get_from_json_value(obj, "decl");
            char *func_name = json_get_string(decl, "name");
            strcpy(func_datas[struct_counter].func_name, func_name);

            // printf("%d 번째 함수 리턴타입 추출 \n", struct_counter + 1);
            json_value decl_below_type = json_get_from_json_value(decl, "type");
            json_value decl_below_type_below_type = json_get_from_json_value(decl_below_type, "type");
            json_value decl_below_type_below_type_below_type = json_get_from_json_value(decl_below_type_below_type, "type");
            json_value return_type_object_json = json_get_from_json_value(decl_below_type_below_type_below_type, "names");

            if (return_type_object_json.type == JSON_ARRAY)
            {
                json_array *return_type_object_array = (json_array *)return_type_object_json.value;
                for (int i = 0; i <= return_type_object_array->last_index; i++)
                {
                    if (return_type_object_array->values[i].type == JSON_STRING)
                    {
                        strcat(func_datas[struct_counter].func_return_type, (char *)return_type_object_array->values[i].value);
                        strcat(func_datas[struct_counter].func_return_type, " ");
                    }
                }
            }
            // printf("%d 함수에서 사용된 파라미터 이름과 파라미터 타입 추출 \n", struct_counter + 1);
            decl_below_type = json_get_from_json_value(decl, "type");
            char *node_type_checker = json_get_string(decl_below_type, "_nodetype");
            if (strcmp(node_type_checker, "FuncDecl") == 0)
            {
                json_value decl_below_type_below_args = json_get_from_json_value(decl_below_type, "args");
                if (json_is_null(decl_below_type_below_args) == 1)
                {
                    // printf("main. or no having parameter\n");
                    parameters[struct_counter] = (Parameter *)malloc(2 * sizeof(Parameter));
                    strcpy(parameters[struct_counter][0].parameter_name, "parameter로 사용된 변수 없음");
                    strcpy(parameters[struct_counter][0].parameter_return_type, "parameter로 사용된 변수 없음");
                    func_datas[struct_counter].parameter_count = 0;
                }
                else
                {

                    char *node_type_checker_second = json_get_string(decl_below_type_below_args, "_nodetype");
                    if (strcmp(node_type_checker_second, "ParamList") == 0)
                    {

                        json_value decl_below_type_below_args_params = json_get_from_json_value(decl_below_type_below_args, "params");
                        // json_print(decl_below_type_below_args_params);
                        if (decl_below_type_below_args_params.type == JSON_ARRAY)
                        {
                            json_array *decl_below_type_below_args_params_array = (json_array *)decl_below_type_below_args_params.value;
                            // printf("%d.\n", decl_below_type_below_args_params_array->last_index+1);
                            int parmeter_counter = decl_below_type_below_args_params_array->last_index + 1;
                            func_datas[struct_counter].parameter_count = parmeter_counter;

                            // 각 행에 대한 열 메모리 할당
                            parameters[struct_counter] = (Parameter *)malloc(parmeter_counter * sizeof(Parameter));
                            if (parameters[struct_counter] == NULL)
                            {
                                printf("Memory allocation failed for columns at row %d\n", i);
                                return;
                            }

                            for (int i = 0; i <= decl_below_type_below_args_params_array->last_index; i++)
                            {
                                // printf("check: %d\n", i);
                                if (decl_below_type_below_args_params_array->values[i].type == JSON_OBJECT)
                                {
                                    // json_print(decl_below_type_below_args_params_array->values[i]);
                                    //  printf("%d.\n", parmeter_counter);
                                    char *parameter_name = json_get_string(decl_below_type_below_args_params_array->values[i], "name");
                                    // printf("parameter name: %s\n",parameter_name);

                                    strcpy(parameters[struct_counter][i].parameter_name, parameter_name);
                                    json_value decl_below_type_below_args_params_array_below_value_below_type = json_get_from_json_value(decl_below_type_below_args_params_array->values[i], "type");
                                    // json_print(decl_below_type_below_args_params_array_below_value_below_type);
                                    json_value decl_below_type_below_args_params_array_below_value_below_type_below_type = json_get_from_json_value(decl_below_type_below_args_params_array_below_value_below_type, "type");
                                    // json_print(decl_below_type_below_args_params_array_below_value_below_type_below_type);
                                    json_value parameter_type_object_json = json_get_from_json_value(decl_below_type_below_args_params_array_below_value_below_type_below_type, "names");
                                    // json_print(parameter_type_object_json);
                                    // printf("\n");
                                    if (parameter_type_object_json.type == JSON_ARRAY)
                                    {
                                        json_array *parameter_type_object_array = (json_array *)parameter_type_object_json.value;
                                        // printf("last_index: %d \n",parameter_type_object_array->last_index);

                                        for (int j = 0; j <= parameter_type_object_array->last_index; j++)
                                        {
                                            if (parameter_type_object_array->values[j].type == JSON_STRING)
                                            {
                                                strcat(parameters[struct_counter][i].parameter_return_type, (char *)parameter_type_object_array->values[j].value);
                                                strcat(parameters[struct_counter][i].parameter_return_type, " ");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            func_datas[struct_counter].parameter_address = parameters;
            // printf("%d 번째 함수에서 사용된 if문 개수 추출\n", struct_counter + 1);
            json_value body = json_get_from_json_value(obj, "body");
            int if_counter = 0;

            json_value body_below_block_items = json_get_from_json_value(body, "block_items");
            if (body_below_block_items.type == JSON_ARRAY)
            {

                // json_print(body_below_block_items);
                json_array *body_below_block_items_array = (json_array *)body_below_block_items.value;
                for (int i = 0; i <= body_below_block_items_array->last_index; i++)
                {
                    if (body_below_block_items_array->values[i].type == JSON_OBJECT)
                    {

                        char *body_below_block_items_array_below_node_type_checker = json_get_string(body_below_block_items_array->values[i], "_nodetype");
                        if (strcmp(body_below_block_items_array_below_node_type_checker, "If") == 0)
                        {
                            // printf("if counter 증가 \n");
                            if_counter++;
                            json_value body_below_block_items_below_iffalse = json_get_from_json_value(body_below_block_items_array->values[i], "iffalse");
                            json_value body_below_block_items_below_iftrue = json_get_from_json_value(body_below_block_items_array->values[i], "iftrue");

                            if (json_is_null(body_below_block_items_below_iffalse) != 1)
                            {
                                char *body_below_block_items_below_iffalse_below_node_type_checker = json_get_string(body_below_block_items_below_iffalse, "_nodetype");
                                if (strcmp(body_below_block_items_array_below_node_type_checker, "If") == 0)
                                {
                                    // printf("if counter 증가 \n");
                                    if_counter++;
                                    if_finder_reculsively_iffalse(body_below_block_items_below_iffalse, &if_counter);
                                }
                                else
                                {

                                    json_value body_below_block_items_below_iffalse_below_stmt = json_get_from_json_value(body_below_block_items_below_iffalse, "stmt");
                                    if_finder_reculsively_iftrue(body_below_block_items_below_iffalse_below_stmt, &if_counter);
                                }
                            }
                            if (json_is_null(body_below_block_items_below_iftrue) != 1)
                            {
                                // json_print(body_below_block_items_below_iftrue);
                                // printf("dfdsf");

                                if_finder_reculsively_iftrue(body_below_block_items_below_iftrue, &if_counter);
                            }
                        }
                        else
                        {

                            // json_print(body_below_block_items_array->values[i]);
                            json_value body_below_block_items_below_stmt = json_get_from_json_value(body_below_block_items_array->values[i], "stmt");
                            if (json_get_type(body_below_block_items_below_stmt) != JSON_UNDEFINED)
                            {

                                // json_print(body_below_block_items_below_stmt);
                                // printf("////////////////////////////////////////////////\n");
                                if_finder_reculsively_iftrue(body_below_block_items_below_stmt, &if_counter);
                            }
                            // json_print(body_below_block_items_below_stmt);
                        }
                    }
                }
            }

            func_datas[struct_counter].func_using_if_count = if_counter;

            struct_counter++;
            // printf("--------------------------------------------\n");
        }
    }

    struct_counter = 0;

    printf("★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n");
    printf("★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n");
    printf("★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n");

    printf("--------------------------------------------\n");
    printf("결과 출력\n");
    printf("--------------------------------------------\n");
    printf("함수의 총 개수 : %d\n", func_counter);
    printf("--------------------------------------------\n");
    for (int i = 0; i < func_counter; i++)
    {
        printf("%d 번째 함수 이름 : %s \n", i + 1, func_datas[i].func_name);
        printf("%d 번째 함수 리턴타입 : %s \n", i + 1, func_datas[i].func_return_type);
        printf("%d 번째 함수에서 사용된 if문 개수 : %d \n", i + 1, func_datas[i].func_using_if_count);

        printf("%d 함수에서 사용된 파라미터 이름과 파라미터 타입 정보 : \n", i + 1);
        if (func_datas[i].parameter_count == 0)
        {
            printf("파라미터 이름 - %s 파라미터 타입 - %s\n", func_datas[i].parameter_address[i][0].parameter_name, func_datas[i].parameter_address[i][0].parameter_return_type);
        }
        else
        {
            for (int j = 0; j < func_datas[i].parameter_count; j++)
            {
                printf("파라미터 이름 - %s 파라미터 타입 - %s\n", func_datas[i].parameter_address[i][j].parameter_name, func_datas[i].parameter_address[i][j].parameter_return_type);
            }
        }
        printf("--------------------------------------------\n");
    }
}

int main()
{
    json_value root = json_read("result.json");
    json_value datas = json_get(root, "ext");
    load_data(datas);
}