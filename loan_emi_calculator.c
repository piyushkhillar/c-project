#include <stdio.h>
#include <math.h>

int main() {
    int cibil, months;
    double amount, rate, emi, total, interest;

    // Ask CIBIL score
    printf("Enter your CIBIL score: ");
    scanf("%d", &cibil);

    // Eligibility check
    if (cibil < 650) {
        printf("\nYour CIBIL score is %d\n", cibil);
        printf("Status: NOT ELIGIBLE for loan (CIBIL below 650)\n");
        return 0;
    }

    printf("\nYour CIBIL score is %d\n", cibil);
    printf("Status: You ARE eligible for the loan!\n");

    // Loan amount
    printf("\nEnter loan amount (INR): ");
    scanf("%lf", &amount);

    // Tenure & Interest Table
    printf("\nAvailable Tenures & Interest Rates:\n");
    printf("---------------------------------------\n");
    printf("12 months  : 10%%\n");
    printf("24 months  : 11.5%%\n");
    printf("36 months  : 11.5%%\n");
    printf("60 months  : 13%%\n");
    printf("---------------------------------------\n");

    // User selects tenure
    printf("\nEnter desired tenure (months): ");
    scanf("%d", &months);

    // Tenure-based base interest
    if (months <= 12) rate = 10;
    else if (months <= 36) rate = 11.5;
    else rate = 13;

    // CIBIL-based risk add-on
    if (cibil >= 650 && cibil <= 699) rate += 2;      // high risk
    else if (cibil >= 700 && cibil <= 749) rate += 1; // medium risk
    // 750+ → no change (best rate)

    // Convert annual % to monthly decimal
    double r = rate / (12 * 100);

    // EMI formula
    double x = pow(1 + r, months);
    emi = amount * r * x / (x - 1);

    total = emi * months;
    interest = total - amount;

    // Final Summary
    printf("\n------ EMI SUMMARY ------\n");
    printf("CIBIL Score       : %d\n", cibil);
    printf("Loan Amount       : %.2f\n", amount);
    printf("Tenure            : %d months\n", months);
    printf("Final Int. Rate   : %.2f %%\n", rate);
    printf("Monthly EMI       : %.2f\n", emi);
    printf("Total Payment     : %.2f\n", total);
    printf("Total Interest    : %.2f\n", interest);
    printf("--------------------------\n");

    return 0;
}



