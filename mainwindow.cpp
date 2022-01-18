#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QNetworkCookie>
#include <QTime>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);

}

MainWindow::~MainWindow() {
  delete ui;


}


void MainWindow::on_pushButton_clicked() {




  QTimer* my_time = new QTimer;

  auto* acc = new QNetworkAccessManager;

  QJsonObject obj;

  this->index=0;
  this->repeat=ui->plainTextEdit_8->toPlainText().toInt();

 QNetworkRequest req;

  if(ui->comboBox->currentText()=="Mofid"){

   req.setUrl(QUrl("https://com/Web/V1/Order/Post"));

   obj["orderCount"] = ui->plainTextEdit_4->toPlainText();
   obj["orderPrice"] = ui->plainTextEdit_3->toPlainText();
   obj["FinancialProviderId"] = 1;
   obj["isin"] = ui->plainTextEdit_2->toPlainText();


  req.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.3; Win64; x64; rv:91.0) Gecko/20100101 Firefox/91.0");


  }else if(ui->comboBox->currentText()=="Saman"){

   req.setUrl(QUrl("https://.ir/Web/V1/Order/Post"));

   obj["CautionAgreementSelected"]=false;
   obj["FinancialProviderId"]=1;
   obj["IsSymbolCautionAgreement"]=false;
   obj["IsSymbolSepahAgreement"]=false;
   obj["SepahAgreementSelected"]=false;
   obj["isin"]= ui->plainTextEdit_2->toPlainText();
   obj["maxShow"]=0;
   obj["minimumQuantity"]=0;
   obj["orderId"]=0;
   obj["orderCount"] = ui->plainTextEdit_4->toPlainText();
   obj["orderPrice"] = ui->plainTextEdit_3->toPlainText();
   obj["orderValiditydate"]=NULL;
   obj["shortSellIncentivePercent"]=0;
   obj["shortSellIsEnabled"]=false;


   req.setHeader(QNetworkRequest::UserAgentHeader,"Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.81 Safari/537.36");
   req.setRawHeader("sec-ch-ua-platform",R"("Windows")");
   req.setRawHeader("Sec-Fetch-Dest","empty");
   req.setRawHeader("Sec-Fetch-Mode","cors");
   req.setRawHeader("Sec-Fetch-Site","same-site");
   req.setRawHeader("sec-ch-ua-mobile","?0");



  }




  if (ui->plainTextEdit_5->toPlainText() == "") obj["orderSide"] = 65;
  else if (ui->plainTextEdit_5->toPlainText() == "") obj["orderSide"] = 86;

  obj["orderValidity"] = 75;


  QByteArray data = QJsonDocument(obj).toJson();


  req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


 




  QTime user_time=QTime::fromString(ui->plainTextEdit_6->toPlainText());


   connect(my_time, &QTimer::timeout, [ = ]() {


    if (QTime::currentTime() >= user_time)  {

        my_time->stop();


      auto *new_timer=new QTimer;

      QObject::connect(new_timer,&QTimer::timeout,[=](){

          QEventLoop loop;

          QNetworkReply* rep = acc->post(req, data);


          ui->textBrowser->append("req sent :" + QTime::currentTime().toString("hh:mm:ss.zzz"));


          QObject::connect(rep, & QNetworkReply:: finished, &loop, &QEventLoop::quit);
          loop.exec();

          ui->textBrowser->append(rep->readAll());

          ui->textBrowser->append("req end :" + QTime::currentTime().toString("hh:mm:ss.zzz"));

          rep->deleteLater();

          this->index++;

          if(index==repeat) new_timer->stop();


      });




    }


    ui->textBrowser_2->setText(QTime::currentTime().toString("hh:mm:ss.zzz"));


  });



  my_time->start(1);


}
