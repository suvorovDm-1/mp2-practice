#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent) {
  stackedWidget = new QStackedWidget(this);
  // Главная страница
  QWidget *mainPage = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout(mainPage);
  QPushButton *findButton = new QPushButton("Найти", this);
  QPushButton *addButton = new QPushButton("Добавить", this);
  QPushButton *deleteButton = new QPushButton("Удалить", this);

  mainLayout->addWidget(findButton);
  mainLayout->addWidget(addButton);
  mainLayout->addWidget(deleteButton);
  mainPage->setLayout(mainLayout);

  // Страница выбора таблицы
  QWidget *tableChoicePage = new QWidget(this);
  QVBoxLayout *tableChoiceLayout = new QVBoxLayout(tableChoicePage);
  QPushButton *scanTableButton = new QPushButton("Просматриваемая таблица", this);
  QPushButton *sortedTableButton = new QPushButton("Сортированная таблица", this);
  QPushButton *hashTableButton = new QPushButton("Хэш таблица", this);

  tableChoiceLayout->addWidget(scanTableButton);
  tableChoiceLayout->addWidget(sortedTableButton);
  tableChoiceLayout->addWidget(hashTableButton);
  tableChoicePage->setLayout(tableChoiceLayout);

  // Страница с таблицей
  QWidget *tablePage = new QWidget(this);
  QVBoxLayout *tableLayout = new QVBoxLayout(tablePage);
  tableWidget = new QTableWidget(0, 2, this);
  tableWidget->setHorizontalHeaderLabels(QStringList() << "Key" << "Value");
  QPushButton *continueButton = new QPushButton("Продолжить", this);

  tableLayout->addWidget(tableWidget);
  tableLayout->addWidget(continueButton);
  tablePage->setLayout(tableLayout);

  // Добавляем страницы в QStackedWidget
  stackedWidget->addWidget(mainPage); // Index 0
  stackedWidget->addWidget(tableChoicePage); // Index 1
  stackedWidget->addWidget(tablePage); // Index 2

  setCentralWidget(stackedWidget);

  // Подключение сигналов и слотов
  connect(findButton, &QPushButton::clicked, this, &MainWindow::showTableChoicePage);
  connect(addButton, &QPushButton::clicked, this, &MainWindow::showTableChoicePage);
  connect(deleteButton, &QPushButton::clicked, this, &MainWindow::showTableChoicePage);

  connect(scanTableButton, &QPushButton::clicked, this, &MainWindow::showTablePage);
  connect(sortedTableButton, &QPushButton::clicked, this, &MainWindow::showTablePage);
  connect(hashTableButton, &QPushButton::clicked, this, &MainWindow::showTablePage);

  connect(continueButton, &QPushButton::clicked, this, &MainWindow::showMainPage);
}

void MainWindow::showMainPage() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showTableChoicePage() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showTablePage() {
    // Здесь вы можете установить разные таблицы в зависимости от нажатой кнопки
    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    stackedWidget->setCurrentIndex(2);
}