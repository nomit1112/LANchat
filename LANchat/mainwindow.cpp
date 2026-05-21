#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add sample nearby users
    ui->usersListWidget->addItem("Aman");
    ui->usersListWidget->addItem("Rahul");
    ui->usersListWidget->addItem("Priya");

    // Show or hide nearby users list
    connect(ui->visibilityCheckBox, &QCheckBox::checkStateChanged,
            this, [=](Qt::CheckState state) {

                if(state == Qt::Checked) {

                    ui->usersListWidget->show();

                } else {

                    ui->usersListWidget->hide();
                }
            });

    // Send button functionality
    connect(ui->sendButton, &QPushButton::clicked, this, [=]() {

        // Get message from input box
        QString message = ui->messageLineEdit->text();

        // Ignore empty messages
        if(message.isEmpty())
            return;

        // Get current time
        QString time = QDateTime::currentDateTime().toString("hh:mm");

        // Final formatted message
        QString finalMessage = "[" + time + "] Me: " + message;

        // Display message in chat area
        ui->chatTextEdit->append(finalMessage);

        // Open file and save chat history
        QFile file("chat_history.txt");

        if(file.open(QIODevice::Append | QIODevice::Text)) {

            QTextStream out(&file);

            // Save message into text file
            out << finalMessage << "\n";

            file.close();
        }

        // Clear input field after sending
        ui->messageLineEdit->clear();
    });

    // Load old chat history when application starts
    QFile file("chat_history.txt");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QTextStream in(&file);

        while(!in.atEnd()) {

            QString line = in.readLine();

            ui->chatTextEdit->append(line);
        }

        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}