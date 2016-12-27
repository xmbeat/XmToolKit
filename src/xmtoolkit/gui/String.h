#ifndef CADENA_H
#define CADENA_H
#ifndef NULL
#define NULL 0
#endif
class Cadena {
private:
	int longitud;
	char *cadena;
	static double pow(int, int);
	void init(const int);
public:
	Cadena();
	Cadena(const unsigned int size);
	Cadena(const int size);
	Cadena(char const *c);
	Cadena(const char c);
	Cadena(const Cadena &c);
	~Cadena();
	Cadena &operator=(const Cadena &c);
	Cadena operator+(const Cadena &c);
	Cadena operator+(const int &i);
	bool operator==(const Cadena &c); //comprueba toda la cadena
	bool operator==(const char *c);
	bool operator!=(const Cadena &c);
	bool operator!=(const char *c);
	Cadena &operator+=(const Cadena &c);
	operator const char *();
	int length();
	Cadena substring(int);
	Cadena substring(int beginIndex, int len);
	char charAt(int index);
	void setChar(int index, const char &c);
	bool equals(const char *c, bool ignoreCase = false);
	bool equals(const Cadena &c, bool ignoreCase = false);
	int inString(const char *c, int index = 0);
	int inString(const Cadena &c, int index = 0); //estoy checando en saber cuando el BOM es factible
	void replace(int start, int len, Cadena &c);
	void replace(int start, int len, char *c);
	int strLen(const char *c);
	char* strCopy(char *dest, const char *origen);
	char* strCopy(char *dest, const char *origen, int inicio, int index,
			int len = 0, bool addZero = false);
	static Cadena toBaseString(int, int);
	static int toInteger(Cadena, int);
	static double strVal(const char *);
	static Cadena strStr(double);
	static Cadena string(char, int);
};
typedef Cadena String;
#endif
