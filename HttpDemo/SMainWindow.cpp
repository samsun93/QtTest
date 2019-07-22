#include "SMainWindow.h"
#include "ui_SMainWindow.h"
#include <QNetworkAccessManager>
#include <QTimer>
#include <QNetworkReply>
SMainWindow::SMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SMainWindow)
{
    ui->setupUi(this);
}

SMainWindow::~SMainWindow()
{
    delete ui;
}

void SMainWindow::on_pushButton_clicked()
{
    QTimer timer;
    timer.setInterval(30);  // 设置超时时间 30 秒
    timer.setSingleShot(true);  // 单次触发

    // 请求 Qt 官网
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(ui->lineEdit->text()));
//    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    QNetworkReply *pReply = manager.get(request);

    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();  // 启动事件循环

    if (timer.isActive())
    {  // 处理响应
        timer.stop();
        if (pReply->error() != QNetworkReply::NoError)
        {
            // 错误处理
            qDebug() << "Error String : " << pReply->errorString();
            QString str;
            str="Error String : " + pReply->errorString();
            ui->textEdit->append(str);
        }
        else
        {
            QVariant variant = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            int nStatusCode = variant.toInt();
            // 根据状态码做进一步数据处理
            QByteArray bytes = pReply->readAll();
            qDebug() << "Status Code : " << nStatusCode<<"   bytes size :  "<<bytes.size();
            QString str;
            str= "Status Code : " + QString::number(nStatusCode)+"   bytes size :  " +QString::number(bytes.size());
            ui->textEdit->append(str);

        }
    }
    else
    {  // 处理超时
        disconnect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        pReply->abort();
        pReply->deleteLater();
        qDebug() << "Timeout";
         ui->textEdit->append("Timeout");
    }
}
