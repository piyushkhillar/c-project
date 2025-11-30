#include <stdio.h>
#include <math.h>   // for pow()

// Function to get base rate according to tenure (months)
double getBaseRate(int months) {
    if (months <= 12) {           // short term
        return 10.0;
    } else if (months <= 36) {    // medium term
        return 11.5;
    } else {                      // long term > 36
        return 13.0;
    }
}

// Function to calculate EMI given principal, annual rate, and months
double calculateEMI(double principal, double annualRate, int months) {
    double monthlyRate = annualRate / (12 * 100); // e.g., 12% -> 0.01
    if (monthlyRate == 0) {
        return principal / months;
    } else {
        double rPowerN = pow(1 + monthlyRate, months);
        return principal * monthlyRate * rPowerN / (rPowerN - 1);
    }
}

int main() {
    int cibil;
    double loanAmount;
    int months;
    double riskAdd = 0.0;
    double annualRate, emi, totalPayment, totalInterest;

    // For showing multiple tenure options
    int tenureOptions[] = {12, 24, 36, 60};
    int numOptions = sizeof(tenureOptions) / sizeof(tenureOptions[0]);

    printf("========== LOAN EMI CALCULATOR ==========\n\n");

    // Step 1: Get CIBIL score
    printf("Enter your CIBIL score (300 - 900): ");
    scanf("%d", &cibil);

    // Basic validation
    if (cibil < 300 || cibil > 900) {
        printf("\nInvalid CIBIL score. It should be between 300 and 900.\n");
        return 0;
    }

    // Step 2: Check eligibility based on CIBIL
    if (cibil < 650) {
        printf("\nBased on your CIBIL score (%d), you are NOT eligible for the loan.\n", cibil);
        printf("Reason: Score below 650 is considered high risk under this model.\n");
        return 0;
    }

    // Step 3: Determine risk add-on based on CIBIL
    if (cibil >= 650 && cibil <= 699) {
        riskAdd = 2.0;  // high risk
    } else if (cibil >= 700 && cibil <= 749) {
        riskAdd = 1.0;  // normal
    } else { // cibil >= 750
        riskAdd = 0.0;  // best customer
    }

    printf("\nYou are ELIGIBLE for the loan based on your CIBIL score: %d\n", cibil);

    // Step 4: Get loan amount
    printf("\nEnter loan amount (in INR): ");
    scanf("%lf", &loanAmount);

    if (loanAmount <= 0) {
        printf("Invalid loan amount.\n");
        return 0;
    }

    // Step 5: Show different interest rates for different periods
    printf("\nAvailable Tenure Options and Interest Rates:\n");
    printf("-----------------------------------------------------------\n");
    printf("Tenure (months) | Base Rate (p.a.) | Final Rate (p.a.)\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < numOptions; i++) {
        int t = tenureOptions[i];
        double baseRate = getBaseRate(t);
        double finalRate = baseRate + riskAdd;
        printf("%14d | %14.2f | %15.2f\n", t, baseRate, finalRate);
    }
    printf("-----------------------------------------------------------\n");

    printf("\nNote: Final Rate = Base Rate (by tenure) + Risk Add (by CIBIL).\n");

    // Step 6: Ask user to choose exact tenure in months
    printf("\nEnter your desired loan tenure in months: ");
    scanf("%d", &months);

    if (months <= 0) {
        printf("Invalid tenure.\n");
        return 0;
    }

    // Step 7: Calculate final rate for chosen tenure
    double baseRateChosen = getBaseRate(months);
    annualRate = baseRateChosen + riskAdd;

    // Step 8: Calculate EMI and totals
    emi = calculateEMI(loanAmount, annualRate, months);
    totalPayment = emi * months;
    totalInterest = totalPayment - loanAmount;

    // Step 9: Display final summary
    printf("\n========== FINAL LOAN SUMMARY ==========\n");
    printf("CIBIL Score            : %d\n", cibil);
    printf("Loan Amount (INR)      : %.2f\n", loanAmount);
    printf("Chosen Tenure (Months) : %d\n", months);
    printf("Base Rate (Tenure)     : %.2f %% p.a.\n", baseRateChosen);
    printf("Risk Add (CIBIL)       : %.2f %% p.a.\n", riskAdd);
    printf("Final Interest Rate    : %.2f %% p.a.\n", annualRate);
    printf("---------------------------------------------\n");
    printf("Monthly EMI            : %.2f INR\n", emi);
    printf("Total Payment          : %.2f INR\n", totalPayment);
    printf("Total Interest Paid    : %.2f INR\n", totalInterest);
    printf("=============================================\n");

    printf("\nNote: This is a simplified academic model inspired by how\n");
    printf("banks decide interest under RBI guidelines. It is NOT an\n");
    printf("official RBI rule or real bank policy.\n");

    return 0;
}
