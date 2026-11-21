#include <stdio.h>
#include <stdlib.h> // для rand(), srand()
#include <math.h>   // для M_PI, fabs()
#include <string.h> // для строк
#include <time.h>   // для srand(time(NULL))

double f(double x) {
    return 1.0/(1.0 + x*x);
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(){
    srand(time(NULL));
    int choice;
    while (1) {
        printf("\n--- LABORATORNAYA RABOTA ---\n");
        printf("Student: Seyidov Huseyn, Group: ITPM-126.\n");
        printf("1. Vychislit' Pi\n");
        printf("2. Lokal'nye maksimumy massiva\n");
        printf("3. Vozrastayushchaya posledovatel'nost'\n");
        printf("4. Perevernut' chisla v massive\n");
        printf("5. Shifr Cezarya\n");
        printf("6. Sortirovka slov po dline\n");
        printf("0. Vyhod\n");
        printf("Vyberite punkt: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Vvedite tochnost: ");
                double eps;
                scanf("%lf", &eps);

                int n = 10;
                double pi_calc = 0.0;
                            
                while (fabs(pi_calc - M_PI) > eps){
                    double h = (1.0 - 0.0) / n;
                    double sum = (f(0) + f(1))/2.0;
                    for (int i=1; i<= n-1;i++){sum += f(0 + i*h);}
                    pi_calc = 4.0 * h * sum;
                    n*=2;
                }
                printf("Pi = %.10f\n",pi_calc);
                printf("n = %d\n",n);
                break;
            }
            case 2:{
                printf("Vvedite dlinnu massiva: ");
                int n;
                scanf("%d",&n);
                int arr[100];
                printf("Vvedite element massiva:\n");
                for (int i =0; i<n; i++){
                    scanf("%d",&arr[i]);
                }

                printf("Vash massiv:\n");
                print_array(arr,n);
                
                printf("Lokalnie maksimumi:\n");
                for (int i=1;i<=n-2;i++){
                    if ( arr[i]>arr[i-1] && arr[i]>arr[i+1] ){
                        printf("%d\n",arr[i]);
                    }
                }
                break;
            }
            case 3:{
                printf("Vvedite dlinnu massiva: ");
                int n;
                scanf("%d",&n);
                int arr[100];
                printf("Vvedite element massiva:\n");
                for (int i =0; i<n; i++){
                    scanf("%d",&arr[i]);
                }

                printf("Vash massiv:\n");
                print_array(arr,n);

                int maxstart=0;
                int maxlen=1;
                int curlen=1;

                for (int i = 1; i<n;i++){
                    if (arr[i]>arr[i-1]){
                        curlen++;
                    }
                    else{
                        if (curlen>maxlen){
                            maxlen=curlen;
                            maxstart=i-curlen;
                            curlen=1;
                        }
                    }
                }

                if (curlen>maxlen){
                    maxlen=curlen;
                    maxstart=n-curlen;
                }
                
                printf("Posledovatelnost: ");
                for (int i = maxstart; i < maxstart + maxlen; i++) {
                    printf("%d ", arr[i]);
                }
                printf("\nDlina: %d\n", maxlen);
            
                break;
            }
            case 4:{
                int arr[30];
                printf("Ishodnyy massiv:\n");
                
                for (int i = 0; i < 30; i++) {
                    // Генерация от 10 до 99999 с обходом лимита rand() = 32767
                    arr[i] = 10 + ((rand() * 32768) + rand()) % 99990;
                    printf("%d ", arr[i]);
                }
                printf("\n");
                
                printf("Perevernutyy massiv:\n");
                for (int i = 0; i < 30; i++) {
                    int num = arr[i];
                    int rev = 0;
                    while (num > 0) {
                        rev = rev * 10 + (num % 10);
                        num /= 10;
                    }
                    arr[i] = rev;
                    printf("%d ", arr[i]);
                }
                printf("\n");
                break;
            }
            case 5: {
                char str[256];
                printf("Vvedite stroku: ");
                scanf(" %255[^\n]", str);
                
                int key = 0;
                int is_encrypt = 0; // Флаг: 1 - шифруем, 0 - расшифровываем
                
                if (str[0] >= '0' && str[0] <= '9') {
                    is_encrypt = 0;
                    key = str[0] - '0';
                    printf("Rezhim: Rashifrovka. Klyuch: %d\n", key);
                } else {
                    is_encrypt = 1;
                    key = 1 + rand() % 9;
                    printf("Rezhim: Shifrovanie. Klyuch: %d\n", key);
                }
                
                printf("Rezultat: ");
                for (int i = 0; str[i] != '\0'; i++) {
                    char c = str[i];
                    
                    if (c >= 'A' && c <= 'Z') {
                        if (is_encrypt) {
                            c = ((c - 'A' + key) % 26) + 'A';
                        } else {
                            c = ((c - 'A' - key + 26) % 26) + 'A'; 
                        }
                    } else if (c >= 'a' && c <= 'z') {
                        if (is_encrypt) {
                            c = ((c - 'a' + key) % 26) + 'a';
                        } else {
                            c = ((c - 'a' - key + 26) % 26) + 'a';
                        }
                    }
                    printf("%c", c);
                }
                printf("\n");
                break;
                }
            case 6:{
                char str[256];
                printf("Vvedite stroku: ");
                scanf(" %255[^\n]", str);
                
                int len = 0;
                while (str[len] != '\0') len++;
                
                for (int current_len = 1; current_len <= len; current_len++) {
                    int start = 0;
                    
                    for (int i = 0; i <= len; i++) {
                        if (str[i] == ' ' || str[i] == '\0') {
                            int word_len = i - start;
                            if (word_len == current_len) {
                                for (int j = start; j < i; j++) {
                                    printf("%c", str[j]);
                                }
                                printf("\n");
                            }
                            start = i + 1;
                        }
                    }
                }
                break;
            }
            case 0: printf("Vyhod...\n"); return 0;
            default: printf("Nevernyy punkt!\n");
        }
    }
    return 0;
}
