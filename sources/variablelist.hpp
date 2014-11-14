#ifndef VARIABLELIST_HPP
#define VARIABLELIST_HPP

#include <QListWidget>

class VariableList : public QListWidget
{	
	/**
	 * \class VariableList
	 * \brief A variable list widget
	 *
	 * A variable list widget that will allow you to show variables and
	 * their contents as a string. It will also create a delete button
	 * to let user delete their variables.
	 *
	 */

		Q_OBJECT
	public:

		/**
		 * @brief Constructor
		 *
		 * Construct an empty VariableList with the given *parent*
		 *
		 * @param parent
		 */
		explicit VariableList(QWidget *parent = 0);

		/**
		 * @brief Add a variable to the list
		 *
		 * Add a variable to the list
		 *
		 * @param name	Variable name
		 * @param content	Content of variable as a string
		 *
		 */
		void VariableList::addVar(QString name, QString content);

	signals:

	public slots:

};

#endif // VARIABLELIST_HPP
