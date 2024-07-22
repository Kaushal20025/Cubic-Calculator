#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the keypad connections
const byte ROW_NUM = 4; // four rows
const byte COLUMN_NUM = 3; // three columns
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'-', '0', '#'}
};
byte pin_rows[ROW_NUM] = {8, 9, 10, 7}; // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {6, A2, A1}; // connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

// Initialize the LCD display with I2C address 0x27 (you may need to change the address)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function prototypes
float readUserFloatInputFromKeypad();
void solveQuadraticEquation(float a, float b, float c);
void solveCubicEquation(float a, float b, float c, float d);

void setup() {
  lcd.begin(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
}

void loop() {
  static char state = '0';
  static bool solved = false;

  if (!solved) {
    if (state == '0') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select equation:");
      lcd.setCursor(0, 1);
      lcd.print("1. Quad 2. Cubic");
      state = 'A'; // Move to the next state
    } else if (state == 'A') {
      char equationType = keypad.getKey();
      if (equationType == '1') {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter A:");
        state = 'B';
      } else if (equationType == '2') {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter A:");
        state = 'C';
      }
    } else if (state == 'B') {
      float a = readUserFloatInputFromKeypad();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter B:");
      float b = readUserFloatInputFromKeypad();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter C:");
      float c = readUserFloatInputFromKeypad();

      solveQuadraticEquation(a, b, c);
      solved = true;
    } else if (state == 'C') {
      float a = readUserFloatInputFromKeypad();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter B:");
      float b = readUserFloatInputFromKeypad();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter C:");
      float c = readUserFloatInputFromKeypad();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter D:");
      float d = readUserFloatInputFromKeypad();

      solveCubicEquation(a, b, c, d);
      solved = true;
    }
  }

  if (solved) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press '#' to");
    lcd.setCursor(0, 1);
    lcd.print("solve new eq.");
    while (keypad.getKey() != '#') {
      // Wait for the '#' key to be pressed to continue
    }
    lcd.clear(); // Clear the LCD display
    solved = false; // Reset the flag to allow solving a new equation
    state = '0'; // Reset the state to the initial state
  }
}

float readUserFloatInputFromKeypad() {
  String input = "";
  while (true) {
    char key = keypad.getKey();
    if (key == '#') {
      return input.toFloat();
    } else if (key == '*' || key == NO_KEY) {
      continue;
    } else if (key) {
      input += key;
      lcd.print(key); // Display the pressed key on the LCD display as the user inputs
    }
  }
}

void solveQuadraticEquation(float a, float b, float c) {
  float discriminant = b * b - 4 * a * c;
  lcd.clear();
  if (discriminant > 0) {
    float root1 = (-b + sqrt(discriminant)) / (2 * a);
    float root2 = (-b - sqrt(discriminant)) / (2 * a);
    lcd.setCursor(0, 0);
    lcd.print("Root 1: ");
    lcd.print(root1);
    lcd.setCursor(0, 1);
    lcd.print("Root 2: ");
    lcd.print(root2);
  } else if (discriminant == 0) {
    float root = -b / (2 * a);
    lcd.setCursor(0, 0);
    lcd.print("Root: ");
    lcd.print(root);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("No real roots.");
  }
}

void solveCubicEquation(float a, float b, float c, float d) {
  // Cardano's formula to solve the cubic equation: ax^3 + bx^2 + cx + d = 0

  if (abs(a) < 1e-6) {
    // Not a cubic equation
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Invalid cubic eq.");
    lcd.setCursor(0, 1);
    lcd.print("'a' cannot be 0.");
    return;
  }

  float p = (3 * a * c - b * b) / (3 * a * a);
  float q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);

  float discriminant = q * q / 4 + p * p * p / 27;

  lcd.clear();
  if (abs(discriminant) < 1e-6) {
    // 3 equal real roots
    float r = -q / 2;
    float root1 = cbrt(r) - b / (3 * a);
    float root2 = root1;
    float root3 = root1;
    lcd.setCursor(0, 0);
    lcd.print("Root 1: ");
    lcd.print(root1);
    lcd.setCursor(0, 1);
    lcd.print("Root 2: ");
    lcd.print(root2);
    delay(2000);
    lcd.clear();
    lcd.print("Root 3: ");
    lcd.print(root3);
  } else if (discriminant > 0) {
    // 1 real root and 2 complex roots
    float r = -q / 2 + sqrt(discriminant);
    float s = cbrt(r);
    float t = -q / 2 - sqrt(discriminant);
    float u = cbrt(t);

    float root1 = s + u - b / (3 * a);
    float realPart2 = -(s + u) / 2;
    float imagPart2 = (s - u) * sqrt(3) / 2;
    float realPart3 = realPart2;
    float imagPart3 = -imagPart2;

    lcd.setCursor(0, 0);
    lcd.print("Root 1: ");
    lcd.print(root1);
    delay(2000);
    lcd.clear();
    lcd.print("Root 2:");
    lcd.setCursor(0, 1);
    lcd.print(realPart2);
    lcd.print("+");
    lcd.print(imagPart2);
    lcd.print("i");
    delay(2000);
    lcd.clear();
    lcd.print("Root 3:");
    lcd.setCursor(0, 1);
    lcd.print(realPart3);
    lcd.print("-");
    lcd.print(imagPart3);
    lcd.print("i");
  } else {
    // 3 distinct real roots
    float theta = acos(-q / (2 * sqrt(-p * p * p / 27)));
    float r = 2 * sqrt(-p / 3);

    float root1 = r * cos(theta / 3) - b / (3 * a);
    float root2 = r * cos((theta + 2 * PI) / 3) - b / (3 * a);
    float root3 = r * cos((theta - 2 * PI) / 3) - b / (3 * a);

    lcd.setCursor(0, 0);
    lcd.print("Root 1: ");
    lcd.print(root1);
    delay(2000);
    lcd.clear();
    lcd.print("Root 2: ");
    lcd.print(root2);
    delay(2000);
    lcd.clear();
