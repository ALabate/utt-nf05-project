#include "detailedlist.hpp"

DetailedList::DetailedList(QWidget *parent) :
	QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::NoSelection);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));
   // connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(customContextMenuRequested(const QPoint&)));

    addElement("B", "A+iBa<br/><br/><br/><table><tr><td>test</td><td>hello</td></tr><tr><td>test</td><td>hello</td></tr></table>");
    addElement("A", "12");
    addElement("C", "12");




}

void DetailedList::addElement(QString title, QString content, bool expanded)
{
    int itemLine = count();

    //Create first line : the title item
    insertItem(itemLine, title);
    list.insert(title, item(itemLine));
    item(itemLine)->setBackground(QPalette().window());
    item(itemLine)->setSizeHint(QSize(item(itemLine)->sizeHint().width(), 20));


    //Create content item
    insertItem(itemLine+1, "");
    list.insert(title, item(itemLine+1));
    //Add his associated label that can show multiline rich text
    QLabel* contentLabel = new QLabel(content, this);
    contentLabel->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    setItemWidget(item(itemLine+1), contentLabel);
    item(itemLine+1)->setSizeHint(QSize(item(itemLine+1)->sizeHint().width(), contentLabel->height()));

    //Create default expanded state
    if(expanded)
    {
        item(itemLine)->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
    }
    else
    {
        item(itemLine+1)->setHidden(true);
        item(itemLine)->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    }
}


void DetailedList::itemClicked(QListWidgetItem* clicked)
{
    //Check if we can find an item associated with the title given
    if(clicked->text() != "" && list.contains(clicked->text()))
    {

        QListWidgetItem* titleItem = list.values(clicked->text()).last();
        QListWidgetItem* contentItem = list.values(clicked->text()).first();

        //Expand if not expanded else reduce
        if(contentItem->isHidden())
        {
            contentItem->setHidden(false);
            QIcon iconFleche = style()->standardIcon(QStyle::SP_ArrowDown);
            titleItem->setIcon(iconFleche);

        }
        else {
            contentItem->setHidden(true);
            QIcon iconFleche = style()->standardIcon(QStyle::SP_ArrowRight);
            titleItem->setIcon(iconFleche);
        }
    }
}

void  DetailedList::DEBUGaddNewVar()
{
    addElement(QString::number(QDateTime::currentMSecsSinceEpoch()), "Test :)");
}
