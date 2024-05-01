#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_FLAVORS 40
#define MAX_ORDERS 100
#define MAX_STOCK 40

struct flavor {
    char name[40];
    float price;
};
struct stock {
    char name[40];
    float price;
    int quantity;
};

struct order {
    char customer_name[50];
    char items_name[100];
    struct flavor flavors[MAX_FLAVORS];
    int num_flavors;
    int num_quantity;
    float total_price;
};

struct order orders[MAX_ORDERS];
int num_orders = 0;
struct stock stocks[MAX_STOCK];
int num_stocks = 0;

struct flavor flavors[] = {
    {"Vanilla", 2.0},
    {"Chocolate", 2.5},
    {"Strawberry", 3.0},
    {"Mint", 3.5},
    {"Caramel", 4.0},
    {"Kulfi" , 5.55},
    {"Mango",20.7}
};
int num_flavors = sizeof(flavors) / sizeof(flavors[0]);
// int num_quantity = sizeof(quantity) / sizeof(quantity[0]);

void add_order() {
    struct order new_order;
   char customer_name[50];
    printf("Enter customer name: ");
    //scanf("%s",&customer_name);
    scanf("%s", new_order.customer_name);
    new_order.num_flavors = 0;
    new_order.total_price = 0;
    while (1) {
        printf("Flavours Available");
        printf("\n1. Vanilla\n2. Chocolate\n3. Strawberry\n4. Mint\n5. Caramel\n6. Kulfi\n7. Mango\n");
        printf("Enter flavor name (or 'done' to finish): ");
        char flavor_name[20];
        scanf("%s", flavor_name);
        if (strcmp(flavor_name, "done") == 0) {
            break;
        }
        int i;
        for (i = 0; i < num_flavors; i++) {
            if (strcmp(flavor_name, flavors[i].name) == 0) {
                if (new_order.num_flavors < MAX_FLAVORS) {
                    new_order.flavors[new_order.num_flavors] = flavors[i];
                    new_order.num_flavors++;
                    new_order.total_price += flavors[i].price;
                    break;
                } else {
                    printf("Maximum flavors reached for this order.\n");
                }
            }
        }
        if (i == num_flavors) {
            printf("Invalid flavor name\n");
        }
    }
    orders[num_orders] = new_order;
    num_orders++;
    //printf("Ordered added sucessfully\n");

FILE *fp;
    fp = fopen("orders.txt", "a+");
    fprintf(fp, "%s\n", new_order.customer_name);
    for (int i = 0; i < new_order.num_flavors; i++) {
        fprintf(fp, "\t%s - $%.2f\n", new_order.flavors[i].name, new_order.flavors[i].price);
    }
    fprintf(fp, "\tTotal price: $%.2f\n", new_order.total_price);
    fclose(fp);

    printf("Ordered added sucessfully\n");
}
void add_stock() {
    printf("Enter stock name: ");
    char stock_name[100];
    scanf("%s", stock_name);
    int i;
    for (i = 0; i < num_stocks; i++) {
        if (strcmp(stock_name, stocks[i].name) == 0) {
            // Stock already exists, update quantity
            printf("Enter quantity to add: ");
            int quantity;
            scanf("%d", &quantity);
            stocks[i].quantity += quantity;
             //FILE *fp;
            // fp = fopen("stocks.txt", "a+");
            // fprintf(fp, "%s %f %d\n", stocks[i].name, stocks[i].price, stocks[i].quantity);
            // fclose(fp);

            return;
        }
    }
    // Stock doesn't exist, add new stock
    if (num_stocks < MAX_STOCK) {
        printf("Enter price: ");
        float total_price;
        scanf("%f", &total_price);
        printf("Enter quantity: ");
        int quantity;
        scanf("%d", &quantity);
        struct stock new_stock = { .price = total_price, .quantity = quantity };
        strncpy(new_stock.name, stock_name, sizeof(new_stock.name));
        stocks[num_stocks] = new_stock;
        
        num_stocks++;
      FILE *fp;
        fp = fopen("stocks.txt", "a+");
        fprintf(fp, "%s %f %d\n", new_stock.name, new_stock.price, new_stock.quantity);
        printf("\tPrice: $%.2f\n", new_stock.price);
        printf("\tQuantity: %d\n", new_stock.quantity);
         fprintf(fp, "\tTotal price: $%.2f\n", new_stock.price * new_stock.quantity);
        fclose(fp);
    }
    else {
        printf("Maximum number of stocks reached.\n");
    
    }
}
    

void view_orders() {
    int i, j;
    for (i = 0; i < num_orders; i++) {
        printf("Order #%d: %s\n", i+1, orders[i].customer_name);
        for (j = 0; j < orders[i].num_flavors; j++) {
            printf("\t%s - $%.2f\n", orders[i].flavors[j].name, orders[i].flavors[j].price);
        }
        printf("\tTotal price: $%.2f\n", orders[i].total_price);
    }
}

void view_stock() {
    int i,j;
    for (i = 0; i < num_stocks; i++) {
        printf("Stock #%d: %s\n",i+1,stocks[i].name);
        for (j = 0; j < stocks[i].quantity; j++) {
            printf("\t%s - $%.2f\n", stocks[i].name, stocks[i].price);
        }
        printf("\tTotal price: $%.2f\n", stocks[i].price * stocks[i].quantity);
        printf("Stock  has been sucefully placed\n");
        
    break;
    }
}

int main() {
    while (1) {
        printf("Welcome to ice-cream parlour:\n");
        fflush(stdin);
        printf("1. Add order\n");
        printf("2. View orders\n");
        printf("3. Add/Update stock\n");
        fflush(stdin);
        printf("4. View added_stock\n");
        printf("5. Quit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_order();
                break;
            case 2:
                view_orders();
                continue;
            case 3:
                add_stock();

            case 4:
                view_stock();
                continue;
            case 5:
                printf("Thankyou for choosing ice-cream parlour\n");
               return 0;
             default:
                printf("Invalid choice.\n");
        }
    }
}
//return 0;