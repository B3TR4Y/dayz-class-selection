typedef array<ref JsonClassMagazine> JsonClassMagazineArray;

class JsonClassItem {
	string name;
	bool selected;
	int quantity;
	
	ref TStringArray attachments;
	ref JsonClassItemArray cargo;
	ref JsonClassMagazineArray magazines;
	
	void JsonClassItem(string w_name, int w_quantity = 0, TStringArray w_attachments = null,  JsonClassItemArray w_cargo = null, JsonClassMagazineArray w_mags = null) {
		name = w_name;
		attachments = w_attachments;
		magazines = w_mags;
		quantity = w_quantity;
		cargo = w_cargo;
	}
};