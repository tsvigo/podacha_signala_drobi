#include <QCoreApplication>

#include <QImage>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QFileDialog>
/*--------------------------------------------------------------------------------------------------------------------*/
 QString BMP_FILE_NAME = "image.bmp"; // название надо брать из диалога выбора файла
/*--------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
/*--------------------------------------------------------------------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Вызов диалога выбора файла
    BMP_FILE_NAME = QFileDialog::getOpenFileName(nullptr, "Выберите файл",
                                    "/home/viktor/1_rukoy_GMP/"
                                                            ,  "bmp Files (*.bmp)");

    QString
        RESULT_FILE_NAME=BMP_FILE_NAME+"_result_vector.bin";

    // Проверка, был ли файл выбран
    if (!BMP_FILE_NAME.isEmpty()) {
        qDebug() << "Выбранный файл:" << BMP_FILE_NAME;
    } else {
        qDebug() << "Файл не был выбран.";
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
    // Загрузка изображения
    QImage image(
   // "input.bmp"
   BMP_FILE_NAME
    );
    if (image.isNull()) {
        qDebug() << "Не удалось загрузить изображение!";
        return -1;
    }

    // Убедитесь, что изображение 10x10 пикселей
    if (image.width() != 10 || image.height() != 10) {
        qDebug() << "Изображение должно быть размером 10x10 пикселей!";
        return -1;
    }

    // Создаем бинарный файл для записи
    QFile file(
   // "output.bin"
   RESULT_FILE_NAME
    );
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Не удалось открыть файл для записи!";
        return -1;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);

    // Преобразование пикселей в дробные числа и запись в файл
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            QColor color = image.pixelColor(x, y);
            
            // Пример нормализации значений каналов до [0.0, 1.0]
            float red = color.red() / 255.0f;
            float green = color.green() / 255.0f;
            float blue = color.blue() / 255.0f;

            // Запись значений в бинарный файл
            out << red << green << blue;
        }
    }

    file.close();
    qDebug() << "Преобразование завершено. Бинарный файл создан.";
    return 0;
/*--------------------------------------------------------------------------------------------------------------------*/
    return a.exec();
}
