#include <iostream>

//NOME TOKENS
#define NIL  256
#define TRUE  257
#define FALSE  258
#define FUNCTION  259
#define RETURN  260
#define END  261
#define IF  262
#define ELSE  263
#define ELSEIF  264
#define THEN  265
#define DO  266
#define UNTIL 267
#define FOR 268
#define WHILE  269
#define REPEAT  270
#define IN  271
#define NOT 272
#define OR  273
#define AND  274
#define BREAK 275
#define RELOP  299
#define ID  300
#define NUM  301
#define LITERAL 314
#define LOCAL 316

//ATRIBUTOS
//OPERADORES
#define SUM 276 // +
#define SUB 277 // -
#define MULT 278 // *
#define DIV 279 // / - divisao
#define EXP 280 // ^
#define AS 281 //isso aqui e o igual `=`.
#define NQ 282 // ~=
#define LE 283 // <=
#define GE 284 // >=
#define LT 285 // <
#define GT 286 // >
#define EQ 287 // ==

//DELIMITADORES
#define OPR 288 // (
#define CPR 289 // )
#define OBC 290 // {
#define CBC 291 // }
#define OBK 292 // [
#define CBK 293 //]
#define SC 294 // ;
#define CO 295 // :
#define CM 296 // ,
#define DOT 297 // .
#define DDOT 298 // . .  ?

//LITERAL
#define QM 315; //"
#define BELL 302; // \a
#define BCKSP 303; // )\b
#define FFEED 304; // \f
#define NLINE 305; // \n
#define CARRET 306; // \r
#define HTAB 307; // \t
#define VTAB 308; // \v
#define BCKSL 309; // contra-barra contra-barra
#define QUOT 310; // \"

//COMMENT 
#define COMMENT 311; // --
#define STRCOM 312; // [[
#define CLSCOM 313; // ]]

int tokenAtual = 0;

struct Token {
	int nome_token;
	int atributo;
};


int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
char* code;


char* readFile(char* fileName)
{
	FILE* file = fopen(fileName, "r");
	char* code;
	int n = 0;
	int c;
	long f_size = 0;

	if (file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	f_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	code = new char(f_size);
	
	while ((c = fgetc(file)) != EOF)
	{
		code[n++] = (char)c;
		//printf("%c", code[n]);
	}
	code[n] = EOF;
	return code;
}

int falhar()
{
	switch (estado)
	{
	case 0: partida = 35; break;

	case 35: partida = 47; break;

	case 47: partida = 49; break;

	case 49: 
		partida = 0;
		//retornar msg de erro
		printf("Erro encontrado no codigo\n");
		cont_sim_lido++;
		break;

	default: printf("Erro do compilador");
	}
	return(partida);
}

Token proximo_token()
{
	Token token;
	char c;
	while (code[cont_sim_lido] != EOF)
	{
		//printf("%c", code[cont_sim_lido]);
		switch (estado)
		{
		case 0:
			c = code[cont_sim_lido];
			if ((c == ' ') || (c == '\n'))
			{
				estado = 0;
				cont_sim_lido++;
			}
			else if (c == '<') estado = 1;
			else if (c == '~') estado = 4;
			else if (c == '=') estado = 6;
			else if (c == '>') estado = 9;

			else if (c == '+') estado = 12;
			else if (c == '-') estado = 13;
			else if (c == '*') estado = 16;
			else if (c == '/') estado = 17;
			else if (c == '^') estado = 18;
			else if (c == ';') estado = 19;
			else if (c == ':') estado = 20;
			else if (c == ',') estado = 21;

			else if (c == '.') estado = 22;
			else if (c == '(') estado = 25;
			else if (c == ')') estado = 26;
			else if (c == '{') estado = 27;
			else if (c == '}') estado = 28;
			else if (c == '[') estado = 29;
			else if (c == ']') estado = 32;

			else
			{
				estado = falhar();
			}
			break;

		//Comeca os <, <=, ~=, >, >=

		case 1: //leu <
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == '=') estado = 2;
			else estado = 3;
			break;

		case 2: //<=
			cont_sim_lido++;
			//printf("<relop, LE>\n");
			token.nome_token = LE;
			token.atributo = LE;
			estado = 0;
			return(token);
			break;

		case 3: //<
			
			//printf("<relop, LT>\n");
			token.nome_token = LT;
			token.atributo = LT;
			estado = 0;
			return(token);
			break;

		case 4: //leu ~
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == '=') estado = 5;
			else estado = falhar();
			break;

		case 5: // ~=
			cont_sim_lido++;
			//printf("<relop, NQ>\n");
			token.nome_token = NQ;
			token.atributo = NQ;
			estado = 0;
			return(token);
			break;


		case 6: // leu =
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == '=') estado = 7;
			else estado = 8;
			break;

		case 7: // ==
			cont_sim_lido++;
			//printf("<relop, AS>\n");
			token.nome_token = AS;
			token.atributo = AS;
			estado = 0;
			return(token);
			break;

		case 8: // =
			cont_sim_lido++;
			//printf("<relop, EQ>\n");
			token.nome_token = EQ;
			token.atributo = EQ;
			estado = 0;
			return(token);
			break;


		case 9: // leu >
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == '=') estado = 10;
			else estado = 11;
			break;

		case 10: //>=
			cont_sim_lido++;
			//printf("<relop, GE>\n");
			token.nome_token = GE;
			token.atributo = GE;
			estado = 0;
			return(token);
			break;

		case 11: //>
			
			//printf("<relop, GT>\n");
			token.nome_token = GT;
			token.atributo = GT;
			estado = 0;
			return(token);
			break;

		//Acaba os <, <=, ~=, >, >=
		//Comeca +, -, --, *, /, ^, ;, :, e ,

		case 12: //Leu +
			cont_sim_lido++;
			//printf("<relop, SUM>\n");
			token.nome_token = SUM;
			token.atributo = SUM;
			estado = 0;
			return(token);
			break;

		case 13: //Leu - ou --
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == '-') estado = 14;
			else estado = 15;
			break;

		case 14: //Leu --
			cont_sim_lido++;
			//printf("<relop, COMMENT>\n");
			token.nome_token = COMMENT;
			token.atributo = COMMENT;
			estado = 0;
			return(token);
			break;

		case 15: //Leu -
			cont_sim_lido++;
			//printf("<relop, SUB>\n");
			token.nome_token = SUB;
			token.atributo = SUB;
			estado = 0;
			return(token);
			break;

		case 16: //Leu *
			cont_sim_lido++;
			//printf("<relop, MULT>\n");
			token.nome_token = MULT;
			token.atributo = MULT;
			estado = 0;
			return(token);
			break;

		case 17: //Leu /
			cont_sim_lido++;
			//printf("<relop, DIV>\n");
			token.nome_token = DIV;
			token.atributo = DIV;
			estado = 0;
			return(token);
			break;

		case 18: //Leu ^
			cont_sim_lido++;
			//printf("<relop, EXP>\n");
			token.nome_token = EXP;
			token.atributo = EXP;
			estado = 0;
			return(token);
			break;

		case 19: //Leu ;
			cont_sim_lido++;
			//printf("<relop, SC>\n");
			token.nome_token = SC;
			token.atributo = SC;
			estado = 0;
			return(token);
			break;

		case 20: //Leu :
			cont_sim_lido++;
			//printf("<relop, CO>\n");
			token.nome_token = CO;
			token.atributo = CO;
			estado = 0;
			return(token);
			break;

		case 21: //Leu ,
			cont_sim_lido++;
			//printf("<relop, CM>\n");
			token.nome_token = CM;
			token.atributo = CM;
			estado = 0;
			return(token);
			break;

			//Acaba +, -, --, *, /, ^, ;, :, e ,
			//Comeca ., . ., (, ), {, }, [, ] , [[, ]], "

		case 22: //Leu . ou ..
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == '.') estado = 23;
			else estado = 24;
			break;

		case 23: //Leu ¨ -> trema ou .. n sei
			cont_sim_lido++;
			//printf("<relop, DDOT>\n");
			token.nome_token = DDOT;
			token.atributo = DDOT;
			estado = 0;
			return(token);
			break;

		case 24: //Leu .
			cont_sim_lido++;
			//printf("<relop, DOT>\n");
			token.nome_token = DOT;
			token.atributo = DOT;
			estado = 0;
			return(token);
			break;

		case 25: //Leu (
			cont_sim_lido++;
			//printf("<relop, OPR>\n");
			token.nome_token = OPR;
			token.atributo = OPR;
			estado = 0;
			return(token);
			break;

		case 26: //Leu )
			cont_sim_lido++;
			//printf("<relop, CPR>\n");
			token.nome_token = CPR;
			token.atributo = CPR;
			estado = 0;
			return(token);
			break;

		case 27: //Leu {
			cont_sim_lido++;
			//printf("<relop, OBC>\n");
			token.nome_token = RELOP;
			token.atributo = OBC;
			estado = 0;
			return(token);
			break;

		case 28: //Leu }
			cont_sim_lido++;
			//printf("<relop, CBC>\n");
			token.nome_token = CBC;
			token.atributo = CBC;
			estado = 0;
			return(token);
			break;

		case 29: //Leu [ ou [[
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == '[') estado = 30;
			else estado = 31;
			break;

		case 30: //Leu [[
			cont_sim_lido++;
			//printf("<relop, STRCOM>\n");
			token.nome_token = STRCOM;
			token.atributo = STRCOM;
			estado = 0;
			return(token);
			break;

		case 31: //Leu [
			cont_sim_lido++;
			//printf("<relop, OBK>\n");
			token.nome_token = OBK;
			token.atributo = OBK;
			estado = 0;
			return(token);
			break;

		case 32: //Leu ] ou ]]
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == ']') estado = 33;
			else estado = 34;
			break;

		case 33: //Leu ]]
			cont_sim_lido++;
			//printf("<relop, CLSCOM>\n");
			token.nome_token = CLSCOM;
			token.atributo = CLSCOM;
			estado = 0;
			return(token);
			break;

		case 34: //Leu ]
			cont_sim_lido++;
			//printf("<relop, CBK>\n");
			token.nome_token = CBK;
			token.atributo = CBK;
			estado = 0;
			return(token);
			break;


		//Acaba ., . ., (, ), {, }, [, ] , [[, ]]
		//Comeca ", /a, /b, /f, /n, //, /r, /t, /v , /"

		case 35: //Estado inicial novo para os \a etc
			c = code[cont_sim_lido];
			if ((c == ' ') || (c == '\n'))
			{
				estado = 0;
				cont_sim_lido++;
			}
			else if (c == '"') estado = 36;
			else if (c == 92) estado = 37;
			else if (c == 7) estado = 38;
			else if (c == 8) estado = 39;
			else if (c == 9) estado = 44;
			else if (c == 10) estado = 41;
			else if (c == 11) estado = 45;
			else if (c == 12) estado = 40;
			else if (c == 13) estado = 43;
			else
			{
				estado = falhar();
			}
			break;

		case 36: //Leu ". No automato está como o 35, e como relop. Mas acho que isso nao faz muito sentido. Basicamente a unica mudanca e que eu inverti o estado 35 e 36. 
			cont_sim_lido++;
			//printf("<LITERAL, QM>\n");
			token.nome_token = LITERAL;
			token.atributo = QM;
			estado = 0;
			return(token);
			break;

		case 37: //Leu \ algo
			cont_sim_lido++;
			c = code[cont_sim_lido];

			if (c == 92) estado = 42;
			else if (c == 'a') estado = 38;
			else if (c == 'b') estado = 39;
			else if (c == 'f') estado = 40;
			else if (c == 'n') estado = 41;
			else if (c == 'r') estado = 43;
			else if (c == 't') estado = 44;
			else if (c == 'v') estado = 45;
			else if (c == '"') estado = 46;
			break;

		case 38: //Leu \a
			cont_sim_lido++;
			//printf("<LITERAL, BELL>\n");
			token.nome_token = LITERAL;
			token.atributo = EXP;
			estado = 0;
			return(token);
			break;

		case 39: //Leu \b
			cont_sim_lido++;
			//printf("<LITERAL, BCKSP>\n");
			token.nome_token = LITERAL;
			token.atributo = BCKSP;
			estado = 0;
			return(token);
			break;

		case 40: //Leu \f
			cont_sim_lido++;
			//printf("<LITERAL, FFEED>\n");
			token.nome_token = LITERAL;
			token.atributo = FFEED;
			estado = 0;
			return(token);
			break;

		case 41: //Leu \n
			cont_sim_lido++;
			//printf("<LITERAL, NLINE>\n");
			token.nome_token = LITERAL;
			token.atributo = NLINE;
			estado = 0;
			return(token);
			break;

		case 42: //Leu contra barra contra barra
			cont_sim_lido++;
			//printf("<LITERAL, BCKSL>\n");
			token.nome_token = LITERAL;
			token.atributo = CM;
			estado = 0;
			return(token);
			break;

		case 43: //Leu \r
			cont_sim_lido++;
			//printf("<LITERAL, CARRET>\n");
			token.nome_token = LITERAL;
			token.atributo = CARRET;
			estado = 0;
			return(token);
			break;

		case 44: //Leu \t
			cont_sim_lido++;
			//printf("<LITERAL, HTAB>\n");
			token.nome_token = LITERAL;
			token.atributo = HTAB;
			estado = 0;
			return(token);
			break;

		case 45: //Leu \v
			cont_sim_lido++;
			//printf("<LITERAL, VTAB>\n");
			token.nome_token = LITERAL;
			token.atributo = VTAB;
			estado = 0;
			return(token);
			break;

		case 46: //Leu \"
			cont_sim_lido++;
			//printf("<LITERAL, QUOT>\n");
			token.nome_token = LITERAL;
			token.atributo = QUOT;
			estado = 0;
			return(token);
			break;

		//Acaba /a, /b, /f, /n, //, /r, /t, /v , /"
		//Comeca NUM

		case 47: //Estado inicial do NUM
			c = code[cont_sim_lido];
			if ((c == ' ') || (c == '\n'))
			{
				estado = 0;
				cont_sim_lido++;
			}
			else if (c >=48 && c<=57) estado = 48;
			else
			{
				estado = falhar();
			}
			break;

		case 48: //Leu DIGIT
			cont_sim_lido++;
			c = code[cont_sim_lido];
			while (c >= 48 && c <= 57) {
				cont_sim_lido++;
				c = code[cont_sim_lido];
			}
			//printf("<NUM>\n");
			token.nome_token = NUM;
			token.atributo = NUM;
			estado = 0;
			return(token);
			break;

		//Acaba NUM
		//Comeca ID

		case 49: //Estado inicial do ID
			c = code[cont_sim_lido];
			if ((c == ' ') || (c == '\n'))
			{
				estado = 0;
				cont_sim_lido++;
			}
			else if (c == 'a') estado = 51;
			else if (c == 'b') estado = 53;
			else if (c == 'd') estado = 55;
			else if (c == 'e') estado = 57;
			else if (c == 'f') estado = 61;
			else if (c == 'i') estado = 65;
			else if (c == 'l') estado = 68;
			else if (c == 'n') estado = 70;
			else if (c == 'o') estado = 73;
			else if (c == 'r') estado = 75;
			else if (c == 't') estado = 78;
			else if (c == 'u') estado = 81;
			else if (c == 'w') estado = 83;
			else if ((c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122)) estado = 50; //c esta entre A...Z ou c = underline ou c esta entre a..z
			else
			{
				estado = falhar();
			}
			break;


		case 50: //Leu _ ou LETRA.

			c = code[cont_sim_lido];
			while ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122)) { //enquanto o inicio de _ ou Letras for seguido por Numeros, Letras ou _.
				cont_sim_lido++;
				c = code[cont_sim_lido];
			}
			//printf("<ID>\n");
			token.nome_token = ID;
			token.atributo = 0;
			estado = 0;
			return(token);
			break;


			// Começa as variaveis reservadas (não tem automatos pois vimos esse erro literalmente de última hora)

		case 51: // Leu a
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'n') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'd') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
						estado = 52;
						break;
					}
				}
			}
			estado = 50;
			break;

		case 52: //Leu AND

			printf("<AND>\n");
			token.nome_token = AND;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 53: // Leu b
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'r') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'e') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'a') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'k') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
								estado = 54;
								break;
							}

						}
					}
				}
			}
			estado = 50;
			break;

		case 54: //Leu BREAK
			//printf("<BREAK>\n");
			token.nome_token = BREAK;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 55: // Leu d
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'o') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
					estado = 56;
					break;
				}
			}

			estado = 50;
			break;

		case 56: //Leu DO

			//printf("<DO>\n");
			token.nome_token = DO;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 57: // Leu e
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'l') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 's') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'e') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'i') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == 'f') {
								cont_sim_lido++;
								c = code[cont_sim_lido];
								if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
									estado = 60;
									break;
								}

							}
						}
						if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
							estado = 59;
							break;
						}
					}
				}
			}
			else if (c == 'n') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'd') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
						estado = 58;
						break;
					}

				}
			}
			estado = 50;
			break;

		case 58: //Leu END

			//printf("<END>\n");
			token.nome_token = END;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 59: //Leu ELSE

			//printf("<ELSE>\n");
			token.nome_token = ELSE;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 60: // Leu ELSEIF

			//printf("<ELSEIF>\n");
			token.nome_token = ELSEIF;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 61: // Leu f
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'o') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'r') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
						estado = 62;
						break;
					}
				}
			}
			else if (c == 'a') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'l') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 's') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'e') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
								estado = 63;
								break;
							}
						}
					}
				}
			}
			else if (c == 'u') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'n') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'c') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 't') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == 'i') {
								cont_sim_lido++;
								c = code[cont_sim_lido];
								if (c == 'o') {
									cont_sim_lido++;
									c = code[cont_sim_lido];
									if (c == 'n') {
										cont_sim_lido++;
										c = code[cont_sim_lido];
										if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
											estado = 64;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
			estado = 50;
			break;

		case 62: //Leu FOR

			//printf("<FOR>\n");
			token.nome_token = FOR;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 63: //Leu FALSE

			//printf("<FALSE>\n");
			token.nome_token = FALSE;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 64: // Leu FUNCTION

			//printf("<FUNCTION>\n");
			token.nome_token = FUNCTION;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 65: // Leu i
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'f') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
					estado = 66;
					break;
				}
			}
			else if (c == 'n') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
					estado = 67;
					break;
				}
			}
			estado = 50;
			break;

		case 66: //Leu IF

			//printf("<IF>\n");
			token.nome_token = IF;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 67: //Leu IN

			//printf("<IN>\n");
			token.nome_token = IN;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 68: // Leu l
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'o') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'c') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'a') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'l') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
								estado = 69;
								break;
							}
						}
					}
				}
			}
			estado = 50;
			break;

		case 69: //Leu LOCAL

			//printf("<LOCAL>\n");
			token.nome_token = LOCAL;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 70: // Leu n
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'i') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'l') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
						estado = 71;
						break;
					}
				}
			}
			else if (c == 'o') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 't') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
						estado = 72;
						break;
					}
				}
			}
			estado = 50;
			break;

		case 71: //Leu NIL

			//printf("<NIL>\n");
			token.nome_token = NIL;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 72: //Leu NOT

			//printf("<NOT>\n");
			token.nome_token = NOT;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 73: // Leu o
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'r') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
					estado = 74;
					break;
				}
			}
			estado = 50;
			break;

		case 74: //Leu OR

			//printf("<OR>\n");
			token.nome_token = OR;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 75: // Leu r
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'e') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'p') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'e') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'a') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == 't') {
								cont_sim_lido++;
								c = code[cont_sim_lido];
								if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
									estado = 76;
									break;
								}
							}
						}
					}
				}
				else if (c == 't') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'u') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'r') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == 'n') {
								cont_sim_lido++;
								c = code[cont_sim_lido];
								if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
									estado = 77;
									break;
								}
							}
						}
					}
				}
			}
			estado = 50;
			break;

		case 76: //Leu REPEAT

			//printf("<REPEAT>\n");
			token.nome_token = REPEAT;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 77: //Leu RETURN

			//printf("<RETURN>\n");
			token.nome_token = RETURN;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 78: // Leu t
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'h') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'e') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'n') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
							estado = 79;
							break;
						}
					}
				}
			}
			else if (c == 'r') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'u') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'e') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
							estado = 80;
							break;
						}
					}
				}
			}
			estado = 50;
			break;

		case 79: //Leu THEN

			//printf("<THEN>\n");
			token.nome_token = THEN;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 80: //Leu TRUE

			//printf("<TRUE>\n");
			token.nome_token = TRUE;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 81: // Leu u
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'n') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 't') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'i') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'l') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
								estado = 82;
								break;
							}
						}
					}
				}
			}
			estado = 50;
			break;

		case 82: //Leu UNTIL

			//printf("<UNTIL>\n");
			token.nome_token = UNTIL;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		case 83: // Leu w
			cont_sim_lido++;
			c = code[cont_sim_lido];
			if (c == 'h') {
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (c == 'i') {
					cont_sim_lido++;
					c = code[cont_sim_lido];
					if (c == 'l') {
						cont_sim_lido++;
						c = code[cont_sim_lido];
						if (c == 'e') {
							cont_sim_lido++;
							c = code[cont_sim_lido];
							if (c == ' ' || !((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c == 95) || (c >= 97 && c <= 122))) {
								estado = 84;
								break;
							}
						}
					}
				}
			}
			estado = 50;
			break;

		case 84: //Leu WHILE

			//printf("<WHILE>\n");
			token.nome_token = WHILE;
			token.atributo = -1;
			estado = 0;
			return(token);
			break;

		//acaba switch
		}
	}
	token.nome_token = EOF;
	//printf("aqui");
	token.atributo = -1;
	return(token);

} 
/*========================================================================================================================================================
================================================Acaba Analise Lexica e comeca Sintatica===================================================================
========================================================================================================================================================*/

int pilhaRegras[500];
int lastPilha = 1;
int contaErro = 0;
bool sinc = 1;
Token tokenSyntax;

void TokenRecebido() {
	if (tokenSyntax.nome_token == DO) printf(" do\n");
	else if (tokenSyntax.nome_token == IN) printf(" in\n");
	else if (tokenSyntax.nome_token == END) printf(" end\n");
	else if (tokenSyntax.nome_token == WHILE) printf(" while\n");
	else if (tokenSyntax.nome_token == FOR) printf(" for\n");
	else if (tokenSyntax.nome_token == IF) printf(" if\n");
	else if (tokenSyntax.nome_token == THEN) printf(" then\n");
	else if (tokenSyntax.nome_token == ELSE) printf(" else\n");
	else if (tokenSyntax.nome_token == ELSEIF) printf(" elseif\n");
	else if (tokenSyntax.nome_token == LOCAL) printf(" local\n");
	else if (tokenSyntax.nome_token == BREAK) printf(" break\n");
	else if (tokenSyntax.nome_token == FUNCTION) printf(" function\n");
	else if (tokenSyntax.nome_token == RETURN) printf(" return\n");
	else if (tokenSyntax.nome_token == NOT) printf(" not\n");
	else if (tokenSyntax.nome_token == NIL) printf(" nil\n");
	else if (tokenSyntax.nome_token == TRUE) printf(" true\n");
	else if (tokenSyntax.nome_token == FALSE) printf(" false\n");
	else if (tokenSyntax.nome_token == CM) printf(" ,\n");
	else if (tokenSyntax.nome_token == OR) printf(" or\n");
	else if (tokenSyntax.nome_token == AND) printf(" and\n");
	else if (tokenSyntax.nome_token == LT) printf(" <\n");
	else if (tokenSyntax.nome_token == GT) printf(" >\n");
	else if (tokenSyntax.nome_token == LE) printf(" <=\n");
	else if (tokenSyntax.nome_token == GE) printf(" >=\n");
	else if (tokenSyntax.nome_token == NQ) printf(" ~=\n");
	else if (tokenSyntax.nome_token == AS) printf(" ==\n");
	else if (tokenSyntax.nome_token == EQ) printf(" =\n");
	else if (tokenSyntax.nome_token == SUM) printf(" +\n");
	else if (tokenSyntax.nome_token == SUB) printf(" -\n");
	else if (tokenSyntax.nome_token == MULT) printf(" *\n");
	else if (tokenSyntax.nome_token == DIV) printf(" /\n");
	else if (tokenSyntax.nome_token == EXP) printf(" ^\n");
	else if (tokenSyntax.nome_token == SC) printf(" ;\n");
	else if (tokenSyntax.nome_token == ID) printf(" Name\n");
	else if (tokenSyntax.nome_token == NUM) printf(" Number\n");
	else if (tokenSyntax.nome_token == LITERAL) printf(" String\n");
	else if (tokenSyntax.nome_token == OPR) printf(" (\n");
	else if (tokenSyntax.nome_token == CPR) printf(" )\n");
	else if (tokenSyntax.nome_token == OBC) printf(" {\n");
	else if (tokenSyntax.nome_token == CBC) printf(" }\n");
	else if (tokenSyntax.nome_token == OBK) printf(" [\n");
	else if (tokenSyntax.nome_token == CBK) printf(" ]\n");
	else if (tokenSyntax.nome_token == DDOT) printf(" ..\n");

}

void EmitirMensagem() {

	if (pilhaRegras[lastPilha] == DO) printf(" do\n");
	else if (pilhaRegras[lastPilha] == IN) printf(" in\n");
	else if (pilhaRegras[lastPilha] == END) printf(" end\n");
	else if (pilhaRegras[lastPilha] == WHILE) printf(" while\n");
	else if (pilhaRegras[lastPilha] == FOR) printf(" for\n");
	else if (pilhaRegras[lastPilha] == IF) printf(" if\n");
	else if (pilhaRegras[lastPilha] == THEN) printf(" then\n");
	else if (pilhaRegras[lastPilha] == ELSE) printf(" else\n");
	else if (pilhaRegras[lastPilha] == ELSEIF) printf(" elseif\n");
	else if (pilhaRegras[lastPilha] == LOCAL) printf(" local\n");
	else if (pilhaRegras[lastPilha] == BREAK) printf(" break\n");
	else if (pilhaRegras[lastPilha] == FUNCTION) printf(" function\n");
	else if (pilhaRegras[lastPilha] == RETURN) printf(" return\n");
	else if (pilhaRegras[lastPilha] == NOT) printf(" not\n");
	else if (pilhaRegras[lastPilha] == NIL) printf(" nil\n");
	else if (pilhaRegras[lastPilha] == TRUE) printf(" true\n");
	else if (pilhaRegras[lastPilha] == FALSE) printf(" false\n");
	else if (pilhaRegras[lastPilha] == CM) printf(" ,\n");
	else if (pilhaRegras[lastPilha] == OR) printf(" or\n");
	else if (pilhaRegras[lastPilha] == AND) printf(" and\n");
	else if (pilhaRegras[lastPilha] == LT) printf(" <\n");
	else if (pilhaRegras[lastPilha] == GT) printf(" >\n");
	else if (pilhaRegras[lastPilha] == LE) printf(" <=\n");
	else if (pilhaRegras[lastPilha] == GE) printf(" >=\n");
	else if (pilhaRegras[lastPilha] == NQ) printf(" ~=\n");
	else if (pilhaRegras[lastPilha] == AS) printf(" ==\n");
	else if (pilhaRegras[lastPilha] == EQ) printf(" =\n");
	else if (pilhaRegras[lastPilha] == SUM) printf(" +\n");
	else if (pilhaRegras[lastPilha] == SUB) printf(" -\n");
	else if (pilhaRegras[lastPilha] == MULT) printf(" *\n");
	else if (pilhaRegras[lastPilha] == DIV) printf(" /\n");
	else if (pilhaRegras[lastPilha] == EXP) printf(" ^\n");
	else if (pilhaRegras[lastPilha] == SC) printf(" ;\n");
	else if (pilhaRegras[lastPilha] == ID) printf(" Name\n");
	else if (pilhaRegras[lastPilha] == NUM) printf(" Number\n");
	else if (pilhaRegras[lastPilha] == LITERAL) printf(" String\n");
	else if (pilhaRegras[lastPilha] == OPR) printf(" (\n");
	else if (pilhaRegras[lastPilha] == CPR) printf(" )\n");
	else if (pilhaRegras[lastPilha] == OBC) printf(" {\n");
	else if (pilhaRegras[lastPilha] == CBC) printf(" }\n");
	else if (pilhaRegras[lastPilha] == OBK) printf(" [\n");
	else if (pilhaRegras[lastPilha] == CBK) printf(" ]\n");
	else if (pilhaRegras[lastPilha] == DDOT) printf(" ..\n");
	else if (pilhaRegras[lastPilha] == 1) printf(" First(Block)\n");
	else if (pilhaRegras[lastPilha] == 2) printf(" First(Stmt)\n");
	else if (pilhaRegras[lastPilha] == 3) printf(" First(S1)\n");
	else if (pilhaRegras[lastPilha] == 4) printf(" First(S2)\n");
	else if (pilhaRegras[lastPilha] == 5) printf(" First(S3)\n");
	else if (pilhaRegras[lastPilha] == 6) printf(" First(Exps)\n");
	else if (pilhaRegras[lastPilha] == 7) printf(" First(Exp)\n");
	else if (pilhaRegras[lastPilha] == 8) printf(" First(E)\n");
	else if (pilhaRegras[lastPilha] == 9) printf(" First(PrefixExp)\n");
	else if (pilhaRegras[lastPilha] == 10) printf(" First(P)\n");
	else if (pilhaRegras[lastPilha] == 11) printf(" First(Field)\n");
	else if (pilhaRegras[lastPilha] == 12) printf(" First(BinOp)\n");
	else if (pilhaRegras[lastPilha] == 13) printf(" First(Vars)\n");
	else if (pilhaRegras[lastPilha] == 14) printf(" First(Var)\n");
	else if (pilhaRegras[lastPilha] == 15) printf(" First(Function)\n");
	else if (pilhaRegras[lastPilha] == 16) printf(" First(FunctionBody)\n");
	else if (pilhaRegras[lastPilha] == 17) printf(" First(Param)\n");
	else if (pilhaRegras[lastPilha] == 18) printf(" First(Names)\n");
	else if (pilhaRegras[lastPilha] == 19) printf(" First(SIf)\n");
	else if (pilhaRegras[lastPilha] == 20) printf(" First(SReturn\n");
	else if (pilhaRegras[lastPilha] == 21) printf(" First(S2a)\n");
	else if (pilhaRegras[lastPilha] == 22) printf(" First(ExpsA)\n");
	else if (pilhaRegras[lastPilha] == 23) printf(" First(ExpA)\n");
	else if (pilhaRegras[lastPilha] == 24) printf(" First(ExpA2)\n");
	else if (pilhaRegras[lastPilha] == 25) printf(" First(F)\n");
	else if (pilhaRegras[lastPilha] == 26) printf(" First(N)\n");
	else if (pilhaRegras[lastPilha] == 27) printf(" First(V)\n");
}

void Sync() {
	printf("Erro Sintatico.\nEsperava ");
	EmitirMensagem(); // Emite o esperado
	printf("Antes de: ");
	TokenRecebido(); // Diz o token recebido da analise lexica
	contaErro += 1;
	lastPilha -= 1;
	sinc = 1;
}

void NeedSync() {
	printf("Erro Sintatico.\nEsperava ");
	EmitirMensagem(); // Emite o esperado
	printf("Antes de: ");
	TokenRecebido(); // Diz o token recebido da analise lexica
	sinc = 0;
	//contaErro += 1;
}

void TrataErro() {
	printf("Erro Sintatico.\n");
	printf("Esperava: ");
	EmitirMensagem(); //Emite token esperado
	printf("Foi recebido: ");
	TokenRecebido(); // Diz o token recebido da analise lexica
	printf("\n");
	lastPilha -= 1;
	contaErro += 1;
	
}

void Block() { //1
	switch (tokenSyntax.nome_token)
	{
	case ID:
		pilhaRegras[lastPilha] = SC; //;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2; //Stmt
		break;

	case OPR:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case FUNCTION:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case DO:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case WHILE:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case IF:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case RETURN:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case BREAK:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case FOR:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case LOCAL:
		pilhaRegras[lastPilha] = SC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2;
		break;

	case EOF:
		lastPilha -= 1;
		break;

	//tokens sync
	case ELSEIF:
		Sync();
		break;

	case ELSE:
		Sync();
		break;

	case END:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void Stmt() { //2
	switch (tokenSyntax.nome_token)
	{
	case ID: //Var = Exps
		pilhaRegras[lastPilha] = 6; // Exps
		lastPilha += 1;
		pilhaRegras[lastPilha] = EQ; // =
		lastPilha += 1;
		pilhaRegras[lastPilha] = 13; // Var
		break;

	case OPR: //Var = Exps
		pilhaRegras[lastPilha] = 6;
		lastPilha += 1;
		pilhaRegras[lastPilha] = EQ;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 13;
		break;

	case FUNCTION: //function Name FunctionBody
		pilhaRegras[lastPilha] = 16; // Function body
		lastPilha += 1;
		pilhaRegras[lastPilha] = 2; // Name
		lastPilha += 1;
		pilhaRegras[lastPilha] = FUNCTION;
		break;

	case DO: // do Block end
		pilhaRegras[lastPilha] = END;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; //Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = DO;
		break;

	case WHILE: // while Exp do Block end
		pilhaRegras[lastPilha] = END;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = DO;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = WHILE;
		break;

	case IF: // if Exp Then Block Sif end 
		pilhaRegras[lastPilha] = END;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 19; // SIf
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = THEN; // Then
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = IF; //if
		break;

	case RETURN: //return SReturn
		pilhaRegras[lastPilha] = 20; // Sreturn
		lastPilha += 1;
		pilhaRegras[lastPilha] = RETURN;
		break;

	case BREAK: // break
		pilhaRegras[lastPilha] = BREAK;
		break;

	case FOR: // for S1
		pilhaRegras[lastPilha] = 3; // S1
		lastPilha += 1;
		pilhaRegras[lastPilha] = FOR;
		break;

	case LOCAL: // local S3
		pilhaRegras[lastPilha] = 5; // S3
		lastPilha += 1;
		pilhaRegras[lastPilha] = LOCAL;
		break;

	//Tokens Sync
	case SC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void S1() { //3
	switch (tokenSyntax.nome_token)
	{
	case ID: //Name S2
		pilhaRegras[lastPilha] = 4; // S2
		lastPilha += 1;
		pilhaRegras[lastPilha] = ID;
		break;

	//Tokens Sync
	case SC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void S2() { //4
	switch (tokenSyntax.nome_token)
	{
	case EQ: //= Exp , Exp S2a do Block end
		pilhaRegras[lastPilha] = END;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = DO;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 21; // S2a
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = CM;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = EQ;
		break;

	case CM: //, Names in Exps do Block end 

		pilhaRegras[lastPilha] = END;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = DO;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 6; //Exps
		lastPilha += 1;
		pilhaRegras[lastPilha] = IN;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 18; // Names
		lastPilha += 1;
		pilhaRegras[lastPilha] = CM;
		break;

	case IN: //in Exps do Block end
		pilhaRegras[lastPilha] = END;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = DO;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 6; //Exps
		lastPilha += 1;
		pilhaRegras[lastPilha] = IN;
		break;

	//Tokens Sync
	case SC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void S3() { //5
	switch (tokenSyntax.nome_token)
	{
	case FUNCTION: // function Name FunctionBody
		pilhaRegras[lastPilha] = 16; // FunctionBody
		lastPilha += 1;
		//pilhaRegras[lastPilha] = ID;
		//lastPilha += 1;
		pilhaRegras[lastPilha] = FUNCTION;
		break;

	case ID: // Names = Exps
		pilhaRegras[lastPilha] = 6; // Exps
		lastPilha += 1;
		pilhaRegras[lastPilha] = EQ;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 18; // Names
		break;

	//Tokens Sync
	case SC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void Exps() { //6
	switch (tokenSyntax.nome_token)
	{
	case NOT: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case SUB: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case ID: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case OPR: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case FUNCTION: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case OBC: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case NIL: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case TRUE: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case FALSE: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case NUM: // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	case LITERAL:  // Exp ExpsA
		pilhaRegras[lastPilha] = 22; // ExpsA
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		break;

	//tokens Sync
	case SC:
		Sync();
		break;

	case DO:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void Exp() { //7
	switch (tokenSyntax.nome_token)
	{
	case NOT: // not Exp E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = NOT;
		break;

	case SUB: // - Exp E

		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = SUB;
		break;

	case ID: // PrefixExp E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = 9; // PrefixExp
		break;

	case OPR: // PrefixExp E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = 9; // PrefixExp
		break;

	case FUNCTION: // Function E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = 15; // Function
		break;

	case OBC: // { ExpA } E
		pilhaRegras[lastPilha] = 8;
		lastPilha += 1;
		pilhaRegras[lastPilha] = CBC;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 23; // ExpA
		lastPilha += 1;
		pilhaRegras[lastPilha] = OBC;
		break;

	case NIL: // nil E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = NIL;
		break;

	case TRUE: // true E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = TRUE;
		break;

	case FALSE: // false E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = FALSE;
		break;

	case NUM: // Number E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = NUM;
		break;

	case LITERAL:  // String E
		pilhaRegras[lastPilha] = 8; // E
		lastPilha += 1;
		pilhaRegras[lastPilha] = LITERAL;
		break;

	//Tokens Sync

	case OR: 
		Sync();
		break;

	case AND: 
		Sync();
		break;

	case LT: 
		Sync();
		break;

	case GT: 
		Sync();
		break;

	case LE:
		Sync();
		break;

	case GE:
		Sync();
		break;

	case NQ:
		Sync();
		break;

	case AS: 
		Sync();
		break;

	case DDOT: 
		Sync();
		break;

	case SUM:
		Sync();
		break;

	/*case SUB:
		Sync();
		break;*/

	case MULT: 
		Sync();
		break;

	case DIV: 
		Sync();
		break;

	case EXP: 
		Sync();
		break;

	case SC:
		Sync();
		break;

	case CBK:
		Sync();
		break;

	case DO:
		Sync();
		break;

	case THEN:
		Sync();
		break;

	case CM:
		Sync();
		break;

	case CPR:
		Sync();
		break;

	case CBC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void E() { //8
	switch (tokenSyntax.nome_token)
	{

	case OR: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case AND: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case LT: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case GT: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case LE: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case GE: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case NQ: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case AS: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case DDOT: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case SUM: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case SUB: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case MULT: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case DIV: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;

	case EXP: // BinOp Exp
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = 12; // BinOp
		break;
	
	case SC: //follow
		lastPilha -= 1;
		break;

	case OBK:
		lastPilha -= 1;
		break;

	case CBK:
		lastPilha -= 1;
		break;

	case DO: 
		lastPilha -= 1;
		break;

	case THEN: 
		lastPilha -= 1;
		break;

	case CM:
		lastPilha -= 1;
		break;

	case CPR: 
		lastPilha -= 1;
		break;

	case END: 
		lastPilha -= 1;
		break;

	case NOT:
		lastPilha -= 1;
		break;

	//case SUB:
		//break;

	case ID:
		lastPilha -= 1;
		break;

	case OPR: 
		lastPilha -= 1;
		break;

	case FUNCTION: 
		lastPilha -= 1;
		break;

	case OBC:
		lastPilha -= 1;
		break;

	case NIL: 
		lastPilha -= 1;
		break;

	case TRUE: 
		lastPilha -= 1;
		break;

	case FALSE: 
		lastPilha -= 1;
		break;

	case NUM:
		lastPilha -= 1;
		break;

	case LITERAL: 
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};

}

void PrefixExp() { //9
	switch (tokenSyntax.nome_token)
	{

	case ID: // Name P
		pilhaRegras[lastPilha] = 10; // P
		lastPilha += 1;
		pilhaRegras[lastPilha] = ID;
		break;

	case OPR: // ( Exp ) P
		pilhaRegras[lastPilha] = 10; // P
		lastPilha += 1;
		pilhaRegras[lastPilha] = CPR;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = OPR;
		break;

		//Tokens Sync

	case OR:
		Sync();
		break;

	case AND:
		Sync();
		break;

	case LT:
		Sync();
		break;

	case GT:
		Sync();
		break;

	case LE:
		Sync();
		break;

	case GE:
		Sync();
		break;

	case NQ:
		Sync();
		break;

	case AS:
		Sync();
		break;

	case DDOT:
		Sync();
		break;

	case SUM:
		Sync();
		break;

	case SUB:
		Sync();
		break;

	case MULT:
		Sync();
		break;

	case DIV:
		Sync();
		break;

	case EXP:
		Sync();
		break;

	case SC:
		Sync();
		break;

	case CBK:
		Sync();
		break;

	case DO:
		Sync();
		break;

	case THEN:
		Sync();
		break;

	case CM:
		Sync();
		break;

	case CPR:
		Sync();
		break;

	case CBC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void P() { //10
	switch (tokenSyntax.nome_token)
	{

	case OBK: // [ Exp ] P
		pilhaRegras[lastPilha] = 10; // P
		lastPilha += 1;
		pilhaRegras[lastPilha] = CBK;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = OBK;
		break;

	case SC: // Follow
		lastPilha -= 1;
		break;

	//case OBK:
		//break;

	case CBK:
		lastPilha -= 1;
		break;

	case DO:
		lastPilha -= 1;
		break;

	case THEN:
		lastPilha -= 1;
		break;

	case CM:
		lastPilha -= 1;
		break;

	case CPR:
		lastPilha -= 1;
		break;

	case CBC:
		lastPilha -= 1;
		break;

	case OR:
		lastPilha -= 1;
		break;

	case AND:
		lastPilha -= 1;
		break;

	case LT:
		lastPilha -= 1;
		break;

	case GT:
		lastPilha -= 1;
		break;

	case LE:
		lastPilha -= 1;
		break;

	case GE:
		lastPilha -= 1;
		break;

	case NQ:
		lastPilha -= 1;
		break;

	case AS:
		lastPilha -= 1;
		break;

	case DDOT:
		lastPilha -= 1;
		break;

	case SUM:
		lastPilha -= 1;
		break;

	case SUB:
		lastPilha -= 1;
		break;

	case MULT:
		lastPilha -= 1;
		break;

	case DIV:
		lastPilha -= 1;
		break;

	case EXP:
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void Field() { //11
	switch (tokenSyntax.nome_token)
	{
	case OBK: // [ Exp ] = Exp
		pilhaRegras[lastPilha] = 7; //Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = EQ;
		lastPilha += 1;
		pilhaRegras[lastPilha] = CBK;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = OBK;
		break;

	case ID: // Name = Exp
		pilhaRegras[lastPilha] = 7; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = EQ;
		lastPilha += 1;
		pilhaRegras[lastPilha] = ID;
		break;

	//Tokens Sync
	case CM:
		Sync();
		break;

	case CBC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void BinOp() { //12
	switch (tokenSyntax.nome_token)
	{
	case OR:
		pilhaRegras[lastPilha] = OR;
		break;

	case AND:
		pilhaRegras[lastPilha] = AND;
		break;

	case LT:
		pilhaRegras[lastPilha] = LT;
		break;

	case GT:
		pilhaRegras[lastPilha] = GT;
		break;

	case LE:
		pilhaRegras[lastPilha] = LE;
		break;

	case GE:
		pilhaRegras[lastPilha] = GE;
		break;

	case NQ:
		pilhaRegras[lastPilha] = NQ;
		break;

	case AS:
		pilhaRegras[lastPilha] = AS;
		break;

	case DDOT:
		pilhaRegras[lastPilha] = DDOT;
		break;

	case SUM:
		pilhaRegras[lastPilha] = SUM;
		break;

	case SUB:
		pilhaRegras[lastPilha] = SUB;
		break;

	case MULT:
		pilhaRegras[lastPilha] = MULT;
		break;

	case DIV:
		pilhaRegras[lastPilha] = DIV;
		break;

	case EXP:
		pilhaRegras[lastPilha] = EXP;
		break;

	//Tokens Sync
	case NOT:
		Sync();
		break;

	/*case SUB:
		Sync();
		break;*/

	case ID:
		Sync();
		break;

	case OPR:
		Sync();
		break;

	case FUNCTION:
		Sync();
		break;

	case OBC:
		Sync();
		break;

	case NIL:
		Sync();
		break;

	case TRUE:
		Sync();
		break;

	case FALSE:
		Sync();
		break;

	case NUM:
		Sync();
		break;

	case LITERAL:
		Sync();
		break;

	default:
		NeedSync();
	};

}

void Vars() { //13
	switch (tokenSyntax.nome_token)
	{
	case ID: // Var V
		pilhaRegras[lastPilha] = 27; // V
		lastPilha += 1;
		pilhaRegras[lastPilha] = 14; // Var
		break;

	case OPR: // Var V
		pilhaRegras[lastPilha] = 27; // V
		lastPilha += 1;
		pilhaRegras[lastPilha] = 14; // Var
		break;

	case EQ:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void Var() { //14
	switch (tokenSyntax.nome_token)
	{
	case ID: // Name
		pilhaRegras[lastPilha] = ID;
		break;

	case OPR: // PrefixExp [ Exp ]
		pilhaRegras[lastPilha] = CBK;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = OBK;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 9; // PrefixExp
		break;

	//Tokens Sync
	case OR:
		Sync();
		break;

	case AND:
		Sync();
		break;

	case LT:
		Sync();
		break;

	case GT:
		Sync();
		break;

	case LE:
		Sync();
		break;

	case GE:
		Sync();
		break;

	case NQ:
		Sync();
		break;

	case AS:
		Sync();
		break;

	case DDOT:
		Sync();
		break;

	case SUM:
		Sync();
		break;

	case SUB:
		Sync();
		break;

	case MULT:
		Sync();
		break;

	case DIV:
		Sync();
		break;

	case EXP:
		Sync();
		break;

	case SC:
		Sync();
		break;

	case CBK:
		Sync();
		break;

	case DO:
		Sync();
		break;

	case THEN:
		Sync();
		break;

	case CM:
		Sync();
		break;

	case CPR:
		Sync();
		break;

	case CBC:
		Sync();
		break;

	case EQ:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void Function() { //15
	switch (tokenSyntax.nome_token)
	{
	case FUNCTION: // function FunctionBody
		pilhaRegras[lastPilha] = 16; // FunctionBody
		lastPilha += 1;
		pilhaRegras[lastPilha] = FUNCTION;
		break;

	//Tokens Sync
	case OR:
		Sync();
		break;

	case AND:
		Sync();
		break;

	case LT:
		Sync();
		break;

	case GT:
		Sync();
		break;

	case LE:
		Sync();
		break;

	case GE:
		Sync();
		break;

	case NQ:
		Sync();
		break;

	case AS:
		Sync();
		break;

	case DDOT:
		Sync();
		break;

	case SUM:
		Sync();
		break;

	case SUB:
		Sync();
		break;

	case MULT:
		Sync();
		break;

	case DIV:
		Sync();
		break;

	case EXP:
		Sync();
		break;

	case SC:
		Sync();
		break;

	case CBK:
		Sync();
		break;

	case DO:
		Sync();
		break;

	case THEN:
		Sync();
		break;

	case CM:
		Sync();
		break;

	case CPR:
		Sync();
		break;

	case CBC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void FunctionBody() { //16
	switch (tokenSyntax.nome_token)
	{
	case ID: // Name ( F ) Block end
		pilhaRegras[lastPilha] = END;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = CPR;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 25; // F
		lastPilha += 1;
		pilhaRegras[lastPilha] = OPR;
		lastPilha += 1;
		pilhaRegras[lastPilha] = ID;
		break;

	//Tokens Sync
	case OR:
		Sync();
		break;

	case AND:
		Sync();
		break;

	case LT:
		Sync();
		break;

	case GT:
		Sync();
		break;

	case LE:
		Sync();
		break;

	case GE:
		Sync();
		break;

	case NQ:
		Sync();
		break;

	case AS:
		Sync();
		break;

	case DDOT:
		Sync();
		break;

	case SUM:
		Sync();
		break;

	case SUB:
		Sync();
		break;

	case MULT:
		Sync();
		break;

	case DIV:
		Sync();
		break;

	case EXP:
		Sync();
		break;

	case SC:
		Sync();
		break;

	case CBK:
		Sync();
		break;

	case DO:
		Sync();
		break;

	case THEN:
		Sync();
		break;

	case CM:
		Sync();
		break;

	case CPR:
		Sync();
		break;

	case CBC:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void Param() { //17
	switch (tokenSyntax.nome_token)
	{
	case ID: // Names
		pilhaRegras[lastPilha] = 18; // Names
		break;

	//Tokens Sync
	case CPR:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void Names() { //18
	switch (tokenSyntax.nome_token)
	{
	case ID: // Name N
		pilhaRegras[lastPilha] = 26; // N
		lastPilha += 1;
		pilhaRegras[lastPilha] = ID;
		break;
	
	//Tokens Sync
	case CPR:
		Sync();
		break;

	case IN:
		Sync();
		break;

	case EQ:
		Sync();
		break;

	default:
		NeedSync();
	};
}

void SIf() { //19
	switch (tokenSyntax.nome_token)
	{
	case ELSEIF: // elseif Exp then Block Sif 
		pilhaRegras[lastPilha] = 19; //SIf
		lastPilha += 1;
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = THEN;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7; // Exp
		lastPilha += 1;
		pilhaRegras[lastPilha] = ELSEIF;
		break;

	case ELSE: // else Block
		pilhaRegras[lastPilha] = 1; // Block
		lastPilha += 1;
		pilhaRegras[lastPilha] = ELSE;
		break;

	case END: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void Sreturn() { //20
	switch (tokenSyntax.nome_token)
	{
	case NOT: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case SUB: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case ID: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case OPR: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case FUNCTION: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case OBC: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case NIL: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case TRUE: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case FALSE: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case NUM: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case LITERAL: // Exps
		pilhaRegras[lastPilha] = 6;
		break;

	case SC: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void S2a() { //21
	switch (tokenSyntax.nome_token)
	{
	case CM: // , Exp
		pilhaRegras[lastPilha] = 7;
		lastPilha += 1;
		pilhaRegras[lastPilha] = CM;
		break;

	case DO: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void ExpsA() { //22
	switch (tokenSyntax.nome_token)
	{
	case CM: // , Exp ExpsA
		pilhaRegras[lastPilha] = 22;
		lastPilha += 1;
		pilhaRegras[lastPilha] = CM;
		break;

	case DO: // follow
		lastPilha -= 1;
		break;

	case SC:
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void ExpA() { //23
	switch (tokenSyntax.nome_token)
	{
	case ID: // Field ExpA2
		pilhaRegras[lastPilha] = 24;  // ExpA2
		lastPilha += 1;
		pilhaRegras[lastPilha] = 11; // Field
		break;

	case OBK: // Field ExpA2
		pilhaRegras[lastPilha] = 24;  // ExpA2
		lastPilha += 1;
		pilhaRegras[lastPilha] = 11; // Field
		break;

	case CBC: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void ExpA2() { //24
	switch (tokenSyntax.nome_token)
	{
	case CM: // , Field ExpA2
		pilhaRegras[lastPilha] = 24; // ExpA2
		lastPilha += 1;
		pilhaRegras[lastPilha] = 11; // Field
		lastPilha += 1;
		pilhaRegras[lastPilha] = CM;
		break;

	case CBC: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void F() { //25
	switch (tokenSyntax.nome_token)
	{
	case ID: // Param
		pilhaRegras[lastPilha] = 17; // Param
		break;

	case CPR: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};

}

void N() { //26
	switch (tokenSyntax.nome_token)
	{
	case CM: // , Name N
		pilhaRegras[lastPilha] = 26; // N
		lastPilha += 1;
		pilhaRegras[lastPilha] = ID;
		lastPilha += 1;
		pilhaRegras[lastPilha] = CM;
		break;

	case CPR: // follow
		lastPilha -= 1;
		break;

	case SC: // follow
		lastPilha -= 1;
		break;

	case IN: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}

void V() { //27
	switch (tokenSyntax.nome_token)
	{
	case CM: // , Var V
		pilhaRegras[lastPilha] = 27; // V
		lastPilha += 1;
		pilhaRegras[lastPilha] = 14;
		lastPilha += 1;
		pilhaRegras[lastPilha] = CM;
		break;

	case OBK: // [Exp]
		pilhaRegras[lastPilha] = CBK;
		lastPilha += 1;
		pilhaRegras[lastPilha] = 7;
		lastPilha += 1;
		pilhaRegras[lastPilha] = OBK;
		break;

	case EQ: // follow
		lastPilha -= 1;
		break;

	default:
		NeedSync();
	};
}


void Consumir() {
	tokenSyntax.nome_token = 0;
	lastPilha -= 1;
}

void CheckSinc() {
	contaErro += 1;
	while (sinc == 0) {
		tokenSyntax = proximo_token();
		printf("%d\n", tokenSyntax.nome_token);
		switch (pilhaRegras[lastPilha])
		{
		case 1:
			Block();
			break;
		case 2:
			Stmt();
			break;
		case 3:
			S1();
			break;
		case 4:
			S2();
			break;
		case 5:
			S3();
			break;
		case 6:
			Exps();
			break;
		case 7:
			Exp();
			break;
		case 8:
			E();
			break;
		case 9:
			PrefixExp();
			break;
		case 10:
			P();
			break;
		case 11:
			Field();
			break;
		case 12:
			BinOp();
			break;
		case 13:
			Vars();
			break;
		case 14:
			Var();
			break;
		case 15:
			Function();
			break;
		case 16:
			FunctionBody();
			break;
		case 17:
			Param();
			break;
		case 18:
			Names();
			break;
		case 19:
			SIf();
			break;
		case 20:
			Sreturn();
			break;
		case 21:
			S2a();
			break;
		case 22:
			ExpsA();
			break;
		case 23:
			ExpA();
			break;
		case 24:
			ExpA2();
			break;
		case 25:
			F();
			break;
		case 26:
			N();
			break;
		case 27:
			V();
			break;
		default:
			contaErro += 1;
			sinc = 1;
			lastPilha -= 1;
			break;

		};
		for (int i = 0; i <= lastPilha; i++) { // Imprime o estado atual da pilha
			printf("%d ", pilhaRegras[i]);
		}
		printf("\n");

		if (pilhaRegras[lastPilha] == tokenSyntax.nome_token) {
			sinc = 1;
			break;
		}
	}
}

void SyntaxCheck() {
	
	pilhaRegras[0] = EOF;
	pilhaRegras[1] = 1; // Starta a pilha com (pilha = Block EOF), Ex: Dps da chamada block Pilha = Stmt ; EOF
	//Token token[500];

	while (lastPilha>=0) {
		
		//token[cont_sim_lido] = proximo_token();
		tokenSyntax = proximo_token();
		TokenRecebido();
		while (tokenSyntax.nome_token != 0) {
			switch (pilhaRegras[lastPilha])
			{
			case 1:
				Block();
				break;
			case 2:
				Stmt();
				break;
			case 3:
				S1();
				break;
			case 4:
				S2();
				break;
			case 5:
				S3();
				break;
			case 6:
				Exps();
				break;
			case 7:
				Exp();
				break;
			case 8:
				E();
				break;
			case 9:
				PrefixExp();
				break;
			case 10:
				P();
				break;
			case 11:
				Field();
				break;
			case 12:
				BinOp();
				break;
			case 13:
				Vars();
				break;
			case 14:
				Var();
				break;
			case 15:
				Function();
				break;
			case 16:
				FunctionBody();
				break;
			case 17:
				Param();
				break;
			case 18:
				Names();
				break;
			case 19:
				SIf();
				break;
			case 20:
				Sreturn();
				break;
			case 21:
				S2a();
				break;
			case 22:
				ExpsA();
				break;
			case 23:
				ExpA();
				break;
			case 24:
				ExpA2();
				break;
			case 25:
				F();
				break;
			case 26:
				N();
				break;
			case 27:
				V();
				break;
			case EOF:
				if (pilhaRegras[lastPilha] == tokenSyntax.nome_token && contaErro == 0) {
					printf("Cadeia reconhecida.");
					return;
				}
				else if ((tokenSyntax.nome_token == EOF) && contaErro > 0) {
					printf("Cadeia rejeitada.\n %d erro(s) encontrado(s).", contaErro);
					return;
				}
				else {
					lastPilha += 1;
					pilhaRegras[lastPilha] = 1;
					break;
				}

			default:
				if (tokenSyntax.nome_token == pilhaRegras[lastPilha]) {
					printf("Consome");
					TokenRecebido();
					printf("\n");
					Consumir();
					break;
				}
				else {
					//printf("Entro tratamento");
					TrataErro();
					break;
				}
			};
			if (sinc == 0) { //Varre a entrada ate achar uma variavel sincronizavel
				CheckSinc();
			}

			for (int i = 0; i <= lastPilha; i++) { // Imprime o estado atual da pilha
				printf("%d ", pilhaRegras[i]);
			}
			printf("\n");
		}
	}
}

int main()
{
	code = readFile("programa.txt");
	SyntaxCheck();
	return 0;
}
