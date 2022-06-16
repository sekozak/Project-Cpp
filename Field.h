
class Field{
public:
	Field() {};
	Field(int t) {
		this->type = t;
	}

	virtual int fieldType() const=0;
	virtual void dmg(int* hp) const = 0;
	void setType(int t) { this->type = t; };
	int getType() { return this->type; };

private:
	int type;
};

class Default : public Field {
public:
	Default() :Field(0) {};
	Default(int t) :Field(t) {};
	int fieldType() const override { return 0; };
	void dmg(int* hp) const override {};
private:
};

class Trap : public Field {
public:
	Trap() :Field(12) {};
	Trap(int t) :Field(t) {};
	int fieldType() const override { return 1; };
	void dmg(int* hp) const override { *hp=(*hp-1); };
private:

};

class Bomb : public Field {
public:
	Bomb() :Field(9) {};
	Bomb(int t) :Field(t) {};
	int fieldType() const override { return 2; };
	void dmg(int* hp) const override { *hp = 0; };
private:

};