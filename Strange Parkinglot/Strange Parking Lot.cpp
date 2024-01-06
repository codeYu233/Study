#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//停车场及过道最大容量信息
int num_park = 3;
int num_path = 4;
//车辆信息
typedef struct {
    char *num;
}Car;

//停车位
typedef struct Parking_space {
    Car car;
    int test_start_time;
    Parking_space* next;
    Parking_space* before;
}Parking_space;

//停车场
typedef struct Parking_lot {
    Parking_space* top;
    Parking_space* bottom;
    int stack_size;
}Parking_lot;

//排队次序
typedef struct Node {
    Car car;
    struct Node* next;
}Node;

//过道
typedef struct Path {
    Node* front;
    Node* rear;
    int queue_size;
}Path;

//初始化队列
int InitQueue(Path* pt) {
    pt->front = pt->rear = (Node*)malloc(sizeof(Node));
    pt->rear->next = NULL;
    pt->queue_size = 0;
    return 1;
}
//进入排队
int InQueue(Path* pt, char* num) {
    //过道未满
    if (pt->queue_size < num_path) {
        printf("停车场已满，进入过道排队\n");
        Node* p;
        p = (Node*)malloc(sizeof(Node));
        p->car.num = num;
        p->next = NULL;

        pt->rear->next = p;
        pt->rear = p;
        pt->queue_size += 1;
        return 1;
    }
    //过道已满
    printf("停车场、过道均已满，暂时无法停车\n");
    return 0;
}
//出队列，进入停车场
int OutQueue(Path* pt, Parking_lot *pl) {
    Node* p;
    Parking_space* p2=(Parking_space*)malloc(sizeof(Parking_space));
    p = pt->front->next;
    pt->front->next = pt->front->next->next;
    pt->queue_size -= 1;
    //转移数据到停车场结构单元
    p2->car.num = p->car.num;
    p2->test_start_time = time(NULL);
    free(p);
    //形成停车场数据
    p2->next = pl->top;
    pl->top->before = p2;
    pl->top = p2;
    pl->stack_size += 1;
    return 1;
}

//初始化停车场
int InitStack(Parking_lot *pl) {
    pl->top = NULL;
    pl->bottom = NULL;
    pl->stack_size = 0;
    return 1;
}
//停入车辆
int Push(Parking_lot *pl,Path*pt) {
char* test_num = (char*)malloc(sizeof(char) * 6);
        printf("输入测试用车牌\n");
        scanf("%s", test_num, 7);
        fflush(stdin);
        if (strlen(test_num) > 6 || strlen(test_num) < 1) {
            printf("输入车牌不规范\n");
            fflush(stdin);
            return 0;
        }

    if (pl->stack_size < num_park) {
        int test_start_time_1=time(NULL); 
        //压栈操作
        Parking_space* newParking_space = (Parking_space*)malloc(sizeof(Parking_space));
        newParking_space->next = pl->top;
        if (pl->top != NULL) {
            pl->top->before = newParking_space;
        }
        pl->top = newParking_space;
        newParking_space->test_start_time = test_start_time_1;
        newParking_space->car.num = test_num;
        pl->stack_size += 1;
        return 1;
    }
    else {
            //停车场已满，尝试进入过道排队
            InQueue(pt, test_num);
        return -1;
        }
    return 0;
}

//离开计费
int count_fee(Parking_space* ps) {
    int delta_time = time(NULL) - ps->test_start_time;
    if (delta_time/8 <= 3) {
        printf("车牌为%s的车收费%d元\n", ps->car.num,5 * (int)(delta_time/8));
    }
    else {
        printf("车牌为%s的车收费%d元\n", ps->car.num, 15 + ((int)(delta_time/8 - 3)) * 10);
    }
    
    return 1;
}

//车辆离开
int Pop(Parking_lot* pl,Path *pt) {
    Parking_space* find = pl->top;
    char *leave_car= (char*)malloc(sizeof(char) * 6);
    int number = 1;

    printf("输入测试用出场车辆车牌\n");
    scanf("%s", leave_car, 7);
    while (getchar() != '\n');
    if ( strlen(leave_car)>6||strlen(leave_car)<1) {
        printf("输入车牌不规范\n");
        fflush(stdin);
        return 0;
    }
    if (pl->stack_size == 0) {
        printf("没有任何车辆可供出场\n");
        return 0;
    }
    //判断是否停车场有该车
    while (strcmp(find->car.num, leave_car) != 0) {
            number += 1;
            if (number > pl->stack_size) {
                printf("没有找到相关车辆，出场失败\n");
                return 0;
            }
            find = find->next;
        }
        //在有该车的情况下进行出场计费
  
    //分首、尾、中三种情况进行链表结点的更新
    if (number == pl->stack_size) {
        pl->bottom = find->before;
        count_fee(find);
        free(find);
    }
    else {
        if (number == 1) {
            pl->top = find->next;
            count_fee(find);
            free(find);
        }
        else {
            find->before->next = find->next;
            count_fee(find);
            free(find);
        }
    }
    pl->stack_size -= 1;
    //如果过道有候车，进入一个车辆
    if (pt->queue_size>0) {
        OutQueue(pt, pl);
    }
    return 1;
}
//打印停车场信息
void PrintParkinglot(Parking_lot *pl){
    printf("当前停有%d辆车，剩余%d车位\n", pl->stack_size, num_park - pl->stack_size);
            printf("车牌号和所停时间(h)为\n");
            Parking_space* temp = pl->top;
            for (int i = 0; i < pl->stack_size; i++) {
                printf("%s   %ld\n", temp->car.num,(time(NULL)-temp->test_start_time)/8);
                temp = temp->next;
            }
}
//打印过道信息
void PrintPath(Path *pt){
         printf("过道有%d辆车，剩余%d车位\n", pt->queue_size, num_path - pt->queue_size);
            printf("车牌号为\n");
            Node* temp2 = pt->front->next;
            for (int i = 0; i < pt->queue_size; i++) {
                printf("%s\n", temp2->car.num);
                temp2 = temp2->next;
            }
}
//菜单
void menu(Parking_lot *pl,Path *pt) {
    while (1) {
        int choice = 0;
        int error_push = -1;
        int error_pop = -1;
        printf("请选择一项功能\n");
        printf("1.停车\n");
        printf("2.离开停车场\n");
        printf("3.展示停车场状态\n");
        scanf("%d", &choice);
        switch (choice) {
        default:
        printf("输入错误\n");
        fflush(stdin);
            break;
        case 1:  
            error_push = Push(pl,pt);
            if (error_push == 1) {
                printf("停车成功\n");
            }
            if (error_push == 0) {
                printf("停车失败\n");
            };
            break;
        case 2: 
            Pop(pl,pt);
            break;
        case 3:
        PrintParkinglot(pl);
        PrintPath(pt);
        break; 
        }

    }
}

int main() {
    int error_push = -1;
    int error_pop = -1;

    Parking_lot* pl=(Parking_lot*)malloc(sizeof(Parking_lot));
    Path* pt = (Path*)malloc(sizeof(Path));

    InitStack(pl);
    InitQueue(pt);

    menu(pl,pt);
    return 1;
}


