# DCF Modeling & Time Value of Money — Detailed Notes

## 1. What is DCF Modeling?

* **Definition:** Discounted Cash Flow (DCF) Modeling is a financial valuation method used to estimate the value of an investment, asset, or company based on its expected future cash flows.
* These cash flows are **discounted back to their present value** using a chosen discount rate (cost of capital / required rate of return).

**Purpose:**

* To evaluate the worthiness of a business or investment.
* To decide on investments, acquisitions, or project viability.

**Main Steps:**

1. Project all future cash flows.
2. Choose a suitable discount rate.
3. Discount the future cash flows to present value.
4. Add them up to get Net Present Value (NPV).

---

## 2. Future Value (FV) and Present Value (PV)

### A) Present Value (PV)

* **Definition:** PV tells you how much a future sum of money is worth today, given a specific rate of return.
* **Formula:**
  $PV = \dfrac{FV}{(1+r)^n}$
* **Where:**

  * FV = future value
  * r = interest rate per period
  * n = number of periods

### B) Future Value (FV)

* **Definition:** FV tells you how much an amount today will grow to after compounding.
* **Formula:**
  $FV = PV \times (1+r)^n$

---

## 3. Annuities – Types, PV & FV Formulas

**Annuity:** A series of equal payments at regular intervals (EMIs, pensions, recurring deposits).

### A) Types:

* **Ordinary Annuity:** Payment at **end** of each period.
* **Annuity Due:** Payment at **start** of each period.

### B) Present Value of Ordinary Annuity

$PV_{annuity} = PMT \times \dfrac{1 - (1+r)^{-n}}{r}$

* PMT = periodic payment

### C) Future Value of Ordinary Annuity

$FV_{annuity} = PMT \times \dfrac{(1+r)^n - 1}{r}$

---

## 4. Perpetuity

* **Definition:** A stream of equal payments at regular intervals, expected to continue forever.
* No FV (because infinite period), but we can find PV.

**Formula:**
$PV = \dfrac{PMT}{r}$

**Use Cases:** Perpetual bonds, pensions, endowments.

---

## 5. Government Pension Example (Perpetuity PV)

Suppose a retired government employee receives **₹40,000 per month forever**. If the expected annual discount rate is 8%:

* Annual payment = ₹40,000 × 12 = ₹480,000
* r = 0.08

$PV = \dfrac{480,000}{0.08} = ₹6,000,000$

👉 The pension’s present value = **₹60 lakhs**.

---

## 6. Excel/Google Sheets Usage

* **PV function:** `=PV(rate, nper, pmt)`
* **FV function:** `=FV(rate, nper, pmt)`
* **For perpetuity:** Use manual formula `=PMT/r`

---

## 7. Formula Reference Table

| Concept                | Formula                       |
| ---------------------- | ----------------------------- |
| Present Value (PV)     | PV = FV / (1+r)^n             |
| Future Value (FV)      | FV = PV × (1+r)^n             |
| PV of Ordinary Annuity | PV = PMT × (1 - (1+r)^-n) / r |
| FV of Ordinary Annuity | FV = PMT × ((1+r)^n - 1) / r  |
| PV of Perpetuity       | PV = PMT / r                  |

---

## 8. Application Summary Table

| Situation             | Formula to Use      | Example                 |
| --------------------- | ------------------- | ----------------------- |
| Single future payment | PV, FV              | Lump sum investment     |
| Series of payments    | PV or FV of Annuity | Loan EMIs, RD           |
| Endless payments      | PV of Perpetuity    | Pension, perpetual bond |
