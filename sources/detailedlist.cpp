#include "detailedlist.hpp"

DetailedList::DetailedList(QWidget *parent) :
	QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::NoSelection);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));
    connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(customContextMenuRequested(const QPoint&)));

}

void DetailedList::addElement(QString title, QString content, bool expanded)
{
	if(!list.contains(title))
	{
		int itemLine;
		//Find alphabetical position
		for(itemLine=0; itemLine<list.keys().count();itemLine++)
		{
			if(list.keys().at(itemLine) > title)
			{
				break;
			}
		}


		//Create first line : the title item
		insertItem(itemLine, title);
		list.insert(title, item(itemLine));
		item(itemLine)->setBackground(QPalette().window());
		item(itemLine)->setSizeHint(QSize(item(itemLine)->sizeHint().width(), 20));


		//Create content item
		insertItem(itemLine+1, "");
		list.insert(title, item(itemLine+1));
		//Add a label that can show multiline rich text
		QLabel* contentLabel = new QLabel(content, this);
		contentLabel->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
		setItemWidget(item(itemLine+1), contentLabel);
		item(itemLine+1)->setSizeHint(QSize(item(itemLine+1)->sizeHint().width(), contentLabel->height()));

		//set default expanded state
		expandElement(title,expanded);
	}
}

void DetailedList::deleteElement(QString title)
{
	//Delete all items
	foreach(QListWidgetItem* item, list.values(title))
	{
		delete(this->itemWidget(item));
		delete(item);
	}
	//Remove element from the data list
	list.remove(title);
}

void DetailedList::UpdateElement(QString title, QString content)
{
	//Check if we can find an item associated with the title given
	QListWidgetItem* contentItem = list.values(title).first();
	if(list.contains(title) && itemWidget(contentItem)->metaObject()->className() == QString("QLabel"))
	{
		QLabel* contentLabel = (QLabel*)itemWidget(contentItem);
		contentLabel->setText(content);
		contentLabel->adjustSize();
		contentItem->setSizeHint(QSize(contentItem->sizeHint().width(), contentLabel->height()));
	}
}

void DetailedList::expandElement(QString title, bool expand)
{
	//Check if we can find an item associated with the title given
	if(list.contains(title))
	{
		QListWidgetItem* titleItem = list.values(title).last();
		QListWidgetItem* contentItem = list.values(title).first();
		if(expand)
		{
			contentItem->setHidden(false);
			titleItem->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
		}
		else
		{
			contentItem->setHidden(true);
			titleItem->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
		}
	}
}


void DetailedList::itemClicked(QListWidgetItem* clicked)
{
	//Check if we can find an item associated with the title given
	if(clicked->text() != "" && list.contains(clicked->text()))
	{
		//Expand if reduced
		QListWidgetItem* contentItem = list.values(clicked->text()).first();
		expandElement(clicked->text(), contentItem->isHidden());
	}
}

void DetailedList::customContextMenuRequested(const QPoint& pos)
{
	QListWidgetItem* clicked = itemAt(pos);
	//Check if we can find an item associated with the title given
	if(clicked->text() != "" && list.contains(clicked->text()))
	{
		QMenu *menu = new QMenu();
		QAction *delAction = new QAction(tr("Delete"), menu);
		delAction->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
		connect(delAction, SIGNAL(triggered()),this,SLOT(deleteTriggered()));
		menu->addAction(delAction);
		menu->popup(viewport()->mapToGlobal(pos));
		contextMenuOrigin = clicked;
	}
}


void DetailedList::deleteTriggered()
{

	//Emit signal to inform outside of the object that an element will be deleted
	emit elementDeleted(contextMenuOrigin->text());

	//Delete the element
	deleteElement(contextMenuOrigin->text());
}
