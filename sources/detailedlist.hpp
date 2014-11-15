#ifndef DETAILEDLIST_HPP
#define DETAILEDLIST_HPP

#include <QListWidget>
#include <QLabel>
#include <QDateTime>

class DetailedList : public QListWidget
{	
	/**
	 * \class DetailedList
	 * \brief A list widget with details when you click on the title line
	 *
	 * A list widget with details when you click on the title line with a
	 * triangle or an arrow that indicate current state.
	 * Each element is composed by to QListWidgetItem : title and content.
	 *
     * **Warning** : As each element is indexed by the title name, it has to
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


	protected slots:
        /**
        * @brief Slot triggered when a click is made on an item
        *
        * Slot triggered when a click is made on an item. This is used to expand and reduce elements when you click on a title.
        *
        * @param clicked A pointer to the clicked item
        */
        void itemClicked(QListWidgetItem* clicked);

    private:
        /**
        * @brief A list that associate title with items
        *
        * A list that associate title with items (the title item and the content item)
        */
        QMultiMap<QString, QListWidgetItem*> list;


    public slots:

        //Debug menu:
        void DEBUGaddNewVar();

};

#endif // DETAILEDLIST_HPP
