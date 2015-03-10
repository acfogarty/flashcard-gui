#include "GrammarFlashcardDialog.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <map>
#include <algorithm>
// #include <random>       // std::default_random_engine
// #include <chrono>       // std::chrono::system_clock

GrammarFlashcardDialog::GrammarFlashcardDialog(QWidget *parent)
    : QDialog(parent)
{

    setWindowTitle(tr("Flashcards"));

    verticalLayout_2 = new QVBoxLayout;
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);

    loadButton = new QPushButton(tr("Load flashcards"));
    questionLabel = new QLabel;
    questionLabel->setFrameStyle(QFrame::StyledPanel);
    questionLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    verticalLayout_2->addWidget(loadButton);
    verticalLayout_2->addWidget(questionLabel);

    horizontalLayout_3 = new QHBoxLayout;

    userAnswerLabel = new QLabel(tr("Your answer:"));
    answerLineEdit = new QLineEdit;

    horizontalLayout_3->addWidget(userAnswerLabel);
    horizontalLayout_3->addWidget(answerLineEdit);

    caseAkkRadioButton = new QRadioButton("Akk");
    caseDatRadioButton = new QRadioButton("Dat");
    caseGenRadioButton = new QRadioButton("Gen");

    horizontalLayout_3->addWidget(caseAkkRadioButton);
    horizontalLayout_3->addWidget(caseDatRadioButton);
    horizontalLayout_3->addWidget(caseGenRadioButton);

    verticalLayout_2->addLayout(horizontalLayout_3);

    checkButton = new QPushButton(tr("Check answer"));

    verticalLayout_2->addWidget(checkButton);

    horizontalLayout_4 = new QHBoxLayout;

    answerLabel = new QLabel;
    answerLabel->setFrameStyle(QFrame::StyledPanel);
    answerLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    horizontalLayout_4->addWidget(answerLabel);

    tickLabel = new QLabel;
    tickLabel->setPixmap(QPixmap(QString::fromUtf8("../../Green_tick.png")));
    tickLabel->setVisible(false);

    horizontalLayout_4->addWidget(tickLabel);

    verticalLayout_2->addLayout(horizontalLayout_4);

    horizontalLayout_2 = new QHBoxLayout;
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    prevButton = new QPushButton(tr("Prev"));
    nextButton = new QPushButton(tr("Next"));

    horizontalLayout_2->addWidget(prevButton);
    horizontalLayout_2->addWidget(nextButton);

    verticalLayout_2->addLayout(horizontalLayout_2);

    setLayout(verticalLayout_2);

    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFlashcardMap()));
    connect(checkButton, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    connect(prevButton, SIGNAL(clicked()), this, SLOT(loadPrevFlashcard()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(loadNextFlashcard()));

    //TODO set currPos to null

} // GrammarFlashcardDialog constructor

void GrammarFlashcardDialog::loadFlashcardMap()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("(*)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        std::cerr << "Cannot open file: " << qPrintable(file.errorString()) << std::endl;
        return;
    }
    QTextStream in(&file);
    QString line,questionString;
    QStringList lineList,answerStringList;

    while (!in.atEnd())
    {
        lineList.clear();
        answerStringList.clear();
        line = in.readLine();
        lineList = line.split(";");
        answerStringList.append(lineList[1].trimmed());
        answerStringList.append(lineList[2].trimmed());
        flashcardMap[lineList[0].trimmed()]=answerStringList;
    }

    QMap<QString,QStringList>::const_iterator ic;
    for (ic=flashcardMap.constBegin();ic!=flashcardMap.constEnd();ic++)
    {
        flashcardVector.push_back(ic.key());
    }

    std::random_shuffle(flashcardVector.begin(), flashcardVector.end());

    //close in
    loadButton->setVisible(false);

    std::vector<QString>::iterator it;
    it = flashcardVector.begin();
    setCurrentPosition(it);
    questionLabel->setText(*it);

}

bool GrammarFlashcardDialog::checkAnswer()
{
    //TODO if currPos is null, show error message saying to load flashcards

    //display correct answer 
    QStringList answerStringList = flashcardMap[*currPos];
    QString answerString = answerStringList[0]+" + "+answerStringList[1];
    answerLabel->setText(answerString);

    //check user's answer
    QString userAnswerString = answerLineEdit->text();
    userAnswerString = userAnswerString.trimmed();
    QString userCaseString;
    if (caseAkkRadioButton->isChecked())
    {
        userCaseString = "Akk";
    } 
    else if (caseDatRadioButton->isChecked())
    {
        userCaseString = "Dat";
    }
    else if (caseGenRadioButton->isChecked())
    {
        userCaseString = "Gen";
    }
    else
    {
        //TODO error 
        userCaseString = "";
    }
   
    if ((userAnswerString==answerStringList[0]) && (userCaseString==answerStringList[1]))
    {
        QPixmap pixmap("Green_tick.png");
        tickLabel->setPixmap(pixmap);
    }
    else
    {
        tickLabel->setPixmap(QPixmap("red-x.png"));
    }
    tickLabel->setVisible(true);

    return true;
}

void GrammarFlashcardDialog::setCurrentPosition(std::vector<QString>::iterator i)
{
    currPos=i;
}

std::vector<QString>::iterator GrammarFlashcardDialog::getCurrentPosition()
{
    return currPos;
}

void GrammarFlashcardDialog::loadPrevFlashcard()
{
    if (currPos == flashcardVector.begin())
    {
        currPos=flashcardVector.end()-1;
    }
    else
    {
        currPos--;
    }
    questionLabel->setText(*currPos);
    resetView();
}

void GrammarFlashcardDialog::loadNextFlashcard()
{
    if (currPos == flashcardVector.end()-1)
    {
        currPos=flashcardVector.begin();
    }
    else
    {
        currPos++;
    }
    questionLabel->setText(*currPos);
    resetView();
}

void GrammarFlashcardDialog::resetView()
{
    answerLineEdit->setText("");
    caseAkkRadioButton->setChecked(false);
    caseDatRadioButton->setChecked(false);
    caseGenRadioButton->setChecked(false);
    answerLabel->setText("");
    tickLabel->setVisible(false);
}
