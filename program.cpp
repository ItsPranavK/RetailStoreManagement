#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <fstream.h>

class itemStore {
	struct item {
		int id;
		char name[50];
		double price;

		item *link;
	}t;

	item *top;

	void initialize() {
		fstream file("itemStore.dat", ios::binary|ios::in);

		while(file.read((char*)&t, sizeof(t))) {
			item *temp = new item;

			temp->id = t.id;
			strcpy(temp->name, t.name);
			temp->price = t.price;

			temp->link = top;
			top = temp;
		}
		file.close();
	}

	void write(item *temp) {
		fstream file("itemStore.dat", ios::binary|ios::app);

		t.id = temp->id;
		strcpy(t.name, temp->name);
		t.price = temp->price;
		t.link = temp->link;

		file.write((char*)&t, sizeof(t));
		file.close();
	}

	public:
		itemStore() {
			top = NULL;

			initialize();
		}

		void addItem() {
			item *temp = new item;

			cout << "ENTER NEW ITEM DETAILS" << endl;

			cout << "Product Id: ";
			cin >> temp->id;
			cout << endl;

			cout << "Product Name: ";
			gets(temp->name);
			cout << endl;

			cout << "Product Price: ";
			cin >> temp->price;
			cout << endl << endl;

			write(temp);

			temp->link = top;
			top = temp;
		}

		void deleteItem() {
			if (top == NULL) {
				cout << "No items exist." << endl << endl;
			}
			else {
				 cout << "Item deleted: " << top->id << " " << top->name << " " << top->price << endl << endl;

				 item *temp = top;
				 top = temp->link;

				 delete temp;
			}
		}

		void displayItem() {
			if (top == NULL) {
				cout << "No items exist." << endl << endl;
			}
			else {
				for (item *temp = top; temp->link != NULL ; temp = temp->link) {
					cout << temp->id << " " << temp->name << " " << temp->price << endl;
				}

				cout << temp->id << " " << temp->name << " " << temp->price << endl << endl;
			}
		}

};

void main() {
	itemStore i;
	i.displayItem();
	i.addItem();
	i.addItem();
	i.displayItem();
}
