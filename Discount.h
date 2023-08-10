
#ifndef DISCOUNT_H
# define DISCOUNT_H


class Discount {
private:
    double loyaltyPoints;
    double totalAmount;

public:
    Discount(double totalAmount);

    void calculateDiscount();
    double getDiscountedAmount();
};

Discount::Discount(double totalAmount) : totalAmount(totalAmount), loyaltyPoints(0.0) {}

void Discount::calculateDiscount() {
    if (totalAmount > 1000) {
        loyaltyPoints = totalAmount * 0.10;
    } else if (totalAmount > 500) {
        loyaltyPoints = totalAmount * 0.05;
    }
}

double Discount::getDiscountedAmount() {
    return totalAmount - loyaltyPoints;
}

#endif