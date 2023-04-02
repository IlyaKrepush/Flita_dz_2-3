#include <stdio.h>
#include <stdlib.h>

int mass_show[100][100];
int mass[100][100];
int mass_heads[100];
int mass_matrix[100][100];
int len_mass = 0;



void check_on_connected(int i , int count){
    if (((i-1)*(i-2)/2)<=count)
        printf("The graph is connected\n");
    else{
        printf("The graph is not connected\n");
    }

}


void create_matrix(int index) {
    FILE *file_get = fopen("C://Users//IlyaK//CLionProjects//FLITA//list_of_edges45.txt", "r");
    int first, second;
    for (int i = 0; i < index + 1; i++) {
        for (int j = 0; j < index + 1; j++) {
            mass_matrix[i][j]=-1;
        }
    }
    for ( int i = 1;i<index+1;i++){
        mass_matrix[i][0]=mass_heads[i-1];
        mass_matrix[0][i]=mass_heads[i-1];
    }
    while (fscanf(file_get,"%d %d",&first,&second)!=EOF){
        for (int i = 1;i<index+1;i++){
            if (mass_matrix[i][0]==first)
                for(int j = 1 ; j<index +1;j++){
                    if (mass_matrix[0][j]==second){
                        mass_matrix[i][j]=1;
                        mass_matrix[j][i]=1;
                    }

                }
        }

    }
    fclose(file_get);

    int count_connect=0,count=0;
    for (int i = 1; i <index+1;i++) {
        for (int j = 1; j+count < index + 1; j++) {
            if (i != j) {
                if (mass_matrix[i][j]==1)
                    count_connect++;
            }
        }
        count++;
    }
    check_on_connected(index,count_connect);



}
int check_on_mass_button(int number, int i,int bug){
    int count_fail = 0;

    for (int j = 0; j<i;j++){
        if (mass_heads[j]==number)
            count_fail++;
    }
    if (count_fail==0){
        mass_heads[i]=number;
        i++;
    }
    return i;

}

void get_graph(){
    FILE* file_get = fopen("C://Users//IlyaK//CLionProjects//FLITA//list_of_edges45.txt","r");
    FILE* file_in = fopen("C://Users//IlyaK//CLionProjects//FLITA//graph.dot","w");

    int first,second,i=0,count_tail=0;
    fprintf(file_in,"graph {\n");
    while (fscanf(file_get,"%d %d",&first,&second)!=EOF){
        i = check_on_mass_button(first,i,second);
        i = check_on_mass_button(second,i,first);

        fprintf(file_in,"%d -- %d\n",first , second);
        if (first!=second){
            count_tail++;
        }
    }
    create_matrix(i);

    fprintf(file_in,"}\n");
    fclose((file_in));
    fclose(file_get);

    system("circo -Tpng -O C://Users//IlyaK//CLionProjects//FLITA//graph.dot");
    system("C://Users//IlyaK//CLionProjects//FLITA//graph.dot.png");

}
void graphic_graph(int len){
    FILE* file = fopen("C://Users//IlyaK//CLionProjects//FLITA//graph.dot","w");

    fprintf(file ,"graph{\n");
    int count = 0;
    for (int i = 1; i <len+1;i++){
        for (int j = 1+count; j<len+1;j++){
            if (mass_show[i][j] == 1){
                fprintf(file,"%d -- %d\n",mass_show[i][0],mass_show[0][j]);
            }

        }
        count++;
    }
    fprintf(file,"}\n");
    fclose(file);
    system("circo -Tpng -O C://Users//IlyaK//CLionProjects//FLITA//graph.dot");
    system("C://Users//IlyaK//CLionProjects//FLITA//graph.dot.png");
}

void show_graph(int len){

    for (int i = 1;i<len+1;i++){
        mass_show[i][0] = mass[i-1][0];
    }
    for (int i = 1;i<len+1;i++){
        mass_show[0][i] = mass[i-1][0];
    }

    for (int i = 1 ; i<len+1;i++){
        for (int j = 1;j<len+1;j++){
            int k = 1;
            while (mass[i-1][k]!=0){
                if (mass[i-1][k] == mass_show[0][j])
                    mass_show[i][j]=1;
                k++;
            }
        }
    }
    printf("Matrix of graph\n");
    for (int i = 0; i < len+1; ++i) {
        for (int j = 0; j < len + 1; ++j) {
            printf("%d\t", mass_show[i][j]);

            if (j == len)
                printf("\n");
        }
    }
    printf("Chose:\n1)Add graph head\n2)Connect graph head\n3)show graphs\n4)create Graph\n");
}
int fail_connect(int first,int second,int len){
    int count = 0 ;
    if (first == second)
        return 2;
    for (int i =0 ; i<len;i++){
        if (first == mass[i][0] || second == mass[i][0])
            count++;
    }
    if (count != 2)
        return 1;
    return 0;
}

int add_graphs(int len_mass){
    printf("How much heads of graphs you want to add?\n");
    int len,input = 0,count_fail = 0;
    scanf("%d", &len);
    printf("Input heads of Graphs,use only numbers ! to exit input zero.\n");
    for (int i = len_mass ; i<len+len_mass;i++){
        scanf("%d", &input);
        if (input == 0) {
            printf("Chose:\n1)Add graph head\n2)Connect graph head\n3)show graphs\n");
            return len_mass;
        }
        for (int j = 0 ; j<i;j++){
            if (mass[j][0] == input){
                printf("Alredy in\n");
                count_fail++;
                i=i-1;
            }
        }
        if (count_fail == 0) {
            mass[i][0] = input;
        }
        count_fail = 0;
    }
    printf("Chose:\n1)Add graph head\n2)Connect graph head\n3)show graphs\n");
    len_mass+=len;
    return len_mass;
}
void connect_graph(int len_mass){
    printf("which graph u want to connect?\n");
    int connect_1,connect_2,connect_fail=0;
    scanf("%d", &connect_1);
    printf("and\n ");
    scanf("%d", &connect_2);

    if (fail_connect(connect_1,connect_2,len_mass) >= 1){
        printf("Your graph head doesnt exist or grap head the same\n");
        return;
    }
    for (int i = 0 ; i < len_mass;i++){
        if (mass[i][0] == connect_1){
            for(int j = 0 ; j<len_mass;j++){
                if (mass[i][j] == connect_2)
                    connect_fail++;
            }
            if (connect_fail==0){
                int k =1;
                while (mass[i][k]!=0){
                    k++;
                }
                mass[i][k]=connect_2;
            }
        }
        if (mass[i][0] == connect_2){
            for(int j = 0 ; j<len_mass;j++){
                if (mass[i][j] == connect_1)
                    connect_fail++;
            }
            if (connect_fail==0){
                int k =1;
                while (mass[i][k]!=0){
                    k++;
                }
                mass[i][k]=connect_1;
            }
        }
    }
    printf("Chose:\n1)Add graph head\n2)Connect graph head\n3)show graphs\n");
}
void switching(char operation){
    switch(operation){
        case '1':{
            len_mass = add_graphs(len_mass);
            break;
        }
        case '2':{
            connect_graph(len_mass);
            break;
        }
        case '3':{
            show_graph(len_mass);
            break;
        }
        case '4':{
            graphic_graph(len_mass);
            break;
        }
        case '5':{
            get_graph();
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n");
            printf("and me ayonami rei.");
            exit(0);
        }
        default:
            break;
    }
}
int main(){
    int  x;
    printf("Chose:\n1)Add graph head\n2)Connect graph head\n3)show graphs\n5)Made graph from file.\n");;
    while ( x != '!') {
        switching(x);
        x = getchar();
    }
    return 0;
}
