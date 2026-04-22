//this is just a demo file
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class PaymentProcessor {
public:
    PaymentProcessor(double taxRate) : tax_rate(taxRate) {}

    double calculateTotal(double price, int quantity, double discount) {
        if (quantity <= 0) {
            return 0.0;
        }

        double subtotal = price * quantity;
        double discounted = subtotal - discount;

        if (discounted < 0) {
            discounted = 0;
        }

        return discounted + (discounted * tax_rate);
    }

    bool processPayment(std::string cardNumber, double amount) {
        if (cardNumber.empty() || amount <= 0) {
            return false;
        }

        std::cout << "Charging card " << cardNumber << " for amount " << amount << std::endl;
        return true;
    }

    std::string generateReceipt(std::string customerName, double totalAmount) {
        return "Customer: " + customerName + ", Total Paid: " + std::to_string(totalAmount);
    }

private:
    double tax_rate;
};

int findUserScore(std::vector<int> scores, int userIndex) {
    if (userIndex < 0 || userIndex >= static_cast<int>(scores.size())) {
        return -1;
    }
    return scores[userIndex];
}

int main() {
    PaymentProcessor processor(0.18);
    double total = processor.calculateTotal(100.0, 2, 10.0);

    if (processor.processPayment("1234-5678-9999", total)) {
        std::cout << processor.generateReceipt("Ayush", total) << std::endl;
    }

    std::vector<int> scores = {50, 60, 75, 90};
    std::cout << "User score: " << findUserScore(scores, 2) << std::endl;

    return 0;
}
