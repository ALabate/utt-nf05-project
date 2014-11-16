#ifndef DETAILEDLIST_HPP
#define DETAILEDLIST_HPP

#include <QListWidget>
#include <QLabel>
#include <QDateTime>
#include <QMenu>
#include <QDebug>

class DetailedList : public QListWidget
{	
	/**
	* @class DetailedList
	* @brief A list widget with details when you click on the title line
	*
	* A list widget with details when you click on the title line with a
	* triangle or an arrow that indicate current state.
	* Each element is composed by to QListWidgetItem : title and content.
	* The list is sorted by title alphabetical order
	*
	* **Warning** : As each element is indexed by the title, it has to
	* be unique.
	*
	*/

	Q_OBJECT
	public:

		/**
		* @brief Constructor
		*
		* Construct an empty DetailedList with the given *parent*
		*
		* @param parent
		*/
		explicit DetailedList(QWidget *parent = 0);

		/**
		* @brief Add a new element to the list
		*
		* Add a new element to the list
		*
		* @param title     Plain text title that is allways visible
		* @param content	Rich text content that will be visible when the user click on the line
		* @param expanded	Choose if the new element will be expanded or not
		*/
		void addElement(QString title, QString content, bool expanded = true);

		/**
		* @brief Delete an element from the list
		*
		* Delete an element from the list
		*
		* @param title    Plain text title of the element that you want to delete
		*/
		void deleteElement(QString title);


		/**
		* @brief Update an element from the list
		*
		* Update an element from the list
		*
		* @param title    Plain text title of the element that you want to update
		* @param content	The new content of the element
		*/
		void UpdateElement(QString title, QString content);


		/**
		* @brief Expand or reduce an element of the list
		*
		* Expand or reduce an element of the list
		*
		* @param title    Plain text title of the element that you want to update
		* @param expand	Choose if the element will be expanded or not
		*/
		void expandElement(QString title, bool expand = true);


	protected slots:
		/**
		* @brief Slot triggered when a click is made on an item
		*
		* Slot triggered when a click is made on an item. This is used to expand and reduce elements when you click on a title.
		*
		* @param clicked A pointer to the clicked item
		*/
		void itemClicked(QListWidgetItem* clicked);

		/**
		* @brief Slot triggered when a right click is made
		*
		* Slot triggered when a right click is made. This will add a context menu on elements that will allow user to delete the element.
		*
		* @param pos	Position of the mouse when the user right click
		*/
		void customContextMenuRequested(const QPoint& pos);

		/**
		* @brief Slot triggered when a click is made on the delete button of the context menu
		*
		* Slot triggered when a click is made on the delete button of the context menu. This will emit the but public elementDeleted signal and then remove the element from the list.
		*/
		void deleteTriggered();

	private:
		/**
		* @brief Help to know where come from a context menu
		*
		* A pointer to a QListWidgetItem that help to know where come from a context menu
		*/
		QListWidgetItem* contextMenuOrigin;
		/**
		* @brief A list that associate title with items
		*
		* A list that associate title with items (the title item and the content item)
		*/
		QMultiMap<QString, QListWidgetItem*> list;

	signals:
		/**
		* @brief Signal emitted when the user delete an element
		*
		* Signal emitted when the user delete an element
		*
		* @param title	The title of the deleted element
		*/
		void elementDeleted(QString title);

};

#endif // DETAILEDLIST_HPP
