//this is second file
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <sstream>
#include <stdexcept>

class PaymentService {
public:
    explicit PaymentService(double taxRate) : tax_rate_(taxRate) {}

    double computeFinalAmount(double unitPrice, int itemCount, double discountValue = 0.0) {
        if (itemCount <= 0) {
            throw std::invalid_argument("itemCount must be greater than zero");
        }

        double subtotal = unitPrice * itemCount;
        double adjustedAmount = subtotal - discountValue;

        if (adjustedAmount < 0.0) {
            adjustedAmount = 0.0;
        }

        return adjustedAmount * (1.0 + tax_rate_);
    }

    bool chargeCard(const std::string& maskedCardNumber, double amount, bool enableAuditLog = true) {
        if (maskedCardNumber.empty()) {
            throw std::invalid_argument("maskedCardNumber cannot be empty");
        }

        if (amount <= 0.0) {
            return false;
        }

        if (enableAuditLog) {
            std::cout << "[AUDIT] Charging card " << maskedCardNumber
                      << " for amount " << amount << std::endl;
        }

        return true;
    }

    std::string buildReceipt(const std::string& customerName, double totalAmount, const std::string& currency = "INR") {
        std::ostringstream receipt;
        receipt << "Customer: " << customerName
                << " | Total Paid: " << totalAmount
                << " " << currency;
        return receipt.str();
    }

private:
    double tax_rate_;
};

std::optional<int> getUserScoreByIndex(const std::vector<int>& scores, int userIndex) {
    if (userIndex < 0 || userIndex >= static_cast<int>(scores.size())) {
        return std::nullopt;
    }
    return scores[userIndex];
}

int main() {
    PaymentService service(0.18);
    double total = 0.0;

    try {
        total = service.computeFinalAmount(100.0, 2, 10.0);

        if (service.chargeCard("****-****-9999", total, true)) {
            std::cout << service.buildReceipt("Ayush", total, "INR") << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Payment failed: " << ex.what() << std::endl;
    }

    std::vector<int> scores = {50, 60, 75, 90};
    auto score = getUserScoreByIndex(scores, 2);

    if (score.has_value()) {
        std::cout << "User score: " << score.value() << std::endl;
    } else {
        std::cout << "User score not found" << std::endl;
    }

    return 0;
}
