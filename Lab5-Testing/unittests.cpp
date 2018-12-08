#include <QtTest/QtTest>
#include <QtWidgets>
#include "mainwindow.cpp"
Q_DECLARE_METATYPE(QDate)
class TestMainWindow: public QObject
{
    Q_OBJECT
private slots:
    void AvgNumLinCode_data();
    void AvgNumLinCode();
    void TestDateEdit();
};

void TestMainWindow::AvgNumLinCode_data()
{
    MainWindow mainwindow;
    QTest::addColumn<QString>("code");
    QTest::addColumn<double>("result");

    QString data1 = "#include <cmath>\n"
                    "#include <iostream>\n"
                    "#include <vector>";
    QString data2 = "int fun1(int a) {\n"
                    "// example of function 1\n"
                    "int b = a;\n"
                    "a++;\n"
                    "\n"
                    "return a;\n"
                    "}\n"
                    "\n"
                    "double fun2(int a) {\n"
                    "// example of function 2\n"
                    "double b = a;\n"
                    "// comment 1\n"
                    "// comment 2\n"
                    "a++;\n"
                    "// comment 3\n"
                    "\n"
                    "return a;\n"
                    "}";

    QTest::newRow("no func")     << data1 << 0.0;
    QTest::newRow("two funcs")    << data2 << 4.0;
}

void TestMainWindow::AvgNumLinCode()
{
    QFETCH(QString, code);
    QFETCH(double, result);

    MainWindow mainwindow;
    mainwindow.code = code;

    QCOMPARE(mainwindow.AvgNumLinCode(), result);
}

void TestMainWindow::TestDateEdit()
{
          QDate date( 1967, 3, 11 );
          QDateEdit dateEdit( date );

          // up-arrow should increase day by one
          QTest::keyClick( &dateEdit, Qt::Key_Up );
          QCOMPARE( dateEdit.date(), date.addDays(1) );

          // we click twice on the "reduce" arrow at the bottom RH corner
          // first we need the widget size to know where to click
          QSize editWidgetSize = dateEdit.size();
          QPoint clickPoint(editWidgetSize.rwidth()-2, editWidgetSize.rheight()-2);
          // issue two clicks
          QTest::mouseClick( &dateEdit, Qt::LeftButton, 0, clickPoint);
          QTest::mouseClick( &dateEdit, Qt::LeftButton, 0, clickPoint);
          // and we should have decreased day by two (one less than original)
          QCOMPARE( dateEdit.date(), date.addDays(-1) );

          QTest::keyClicks( &dateEdit, "25122005" );
          QCOMPARE( dateEdit.date(), QDate( 2005, 12, 25 ) );

          QTest::keyClick( &dateEdit, Qt::Key_Tab, Qt::ShiftModifier );
          QTest::keyClicks( &dateEdit, "08" );
          QCOMPARE( dateEdit.date(), QDate( 2005, 8, 25 ) );
//    QPushButton result;
//    result.show();
//    QCOMPARE(result.clicked(), false);
//    QTest::mouseClick(&result, Qt::LeftButton);
//    QCOMPARE(result.clicked(), true);
}

QTEST_MAIN(TestMainWindow)
#include "unittests.moc"
