#include<bits/stdc++.h>
using namespace std;

#define VOCABULARY_FILE "vocab.txt"
#define REVIEW_COUNT 	10
int totalVocab = 0;


class Vocab
{
	private: 
		string word;
		int level;
		std::tm date_added;
		std::tm date_last_reviewed;
		string meaning;
		int nExample;
		std::vector<string> example_sentences;

	public:
		Vocab(){}
		Vocab(string _word, string _meaning, int _nExample, std::vector<string> _example_sentences){
			this->word = _word;	
			this->meaning = _meaning;
			this->nExample = _nExample;
			this->example_sentences = _example_sentences;

			// Set current local datetime
			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);
	 	    this->date_added = *now;
	 	    this->date_last_reviewed = *now;
			this->level = 1;
		}
		Vocab(string _word, int _level, string _meaning, std::tm _date_added, std::tm _date_last_reviewed, int _nExample, std::vector<string> _example_sentences){
			this->word = _word;	
			this->meaning = _meaning;
			this->nExample = _nExample;
			this->example_sentences = _example_sentences;
	 	    this->date_added = _date_added;
	 	    this->date_last_reviewed = _date_last_reviewed;
			this->level = _level;
		}

		void setWord(string _word){
			this->word = _word;
		}

		void setLevel(int _level){
			this->level = _level;
		}

		void setDateLastReviewed(std::tm _date_last_reviewed){
			this->date_last_reviewed = _date_last_reviewed;
		}

		void setMeaning(string _meaning){
			this->meaning = _meaning;
		}

		void setExampleSentences(std::vector<string> _example_sentences){
			this->example_sentences = _example_sentences;
		}

		void addExample(string example){
			this->example_sentences.push_back(example);
			this->nExample++;
		}

		string getWord(){
			return this->word;
		}

		string getMeaning(){
			return this->meaning;
		}

		int getLevel(){
			return this->level;
		}

		int getNExample(){
			return this->nExample;
		}

		std::vector<string> getExampleSentences(){
			return this->example_sentences;
		}

		std::tm getDateAdded(){
			return this->date_added;
		}

		std::tm getDateLastReviewed(){
			return this->date_last_reviewed;
		}

		void displayVocabSummary(){
			std::cout << "Vocab summary:" << endl;
			std::cout << left << setw(20) << "Word: " << this->word << '\n'
					  << left << setw(20) << "Level: " << this->level << '\n'
					  << left << setw(20) << "Meaning: " << this->meaning << '\n';

			std::tm n = this->date_added;
		    get_time(&n, "%d.%m.%Y");
		    std::cout << left << setw(20) << "Date Added: " << (&n)->tm_mday << '.' << (&n)->tm_mon + 1 << '.' << (&n)->tm_year + 1900 << '\n';

		    n = this->date_last_reviewed;
		    get_time(&n, "%d.%m.%Y");
		    std::cout << left << setw(20) << "Date Last Reviewed: " << (&n)->tm_mday << '.' << (&n)->tm_mon + 1 << '.' << (&n)->tm_year + 1900 << '\n';

	    	std::vector<string> _example_sentences = this->example_sentences;
	    	std::vector<string>::iterator it;
	    	int count = 0;

	    	for(it = _example_sentences.begin(); it!=_example_sentences.end(); it++){
	    		count++;
	    		if(count == 1)std::cout << "Example Sentences:\n";
				std::cout << count << ". " << *it << '\n';
			}
			std::cout << endl;
		}
};

class Hash
{
	public:
	    int BUCKET;
	    list<int> *table;

	    Hash(int _BUCKET){
	    	this->BUCKET = _BUCKET;
    		table = new list<int>[BUCKET];
	    }
	 
	    void insertItem(string str, int x){
	    	int index = hashFunction(str);
    		table[index].push_back(x);
	    }
	 
	    int deleteItem(string str, int x){
	    	int deleted = 0;
			int index = hashFunction(str);
			 
			list <int> :: iterator i;
			for (i = table[index].begin(); i != table[index].end(); i++) {
				if (*i == x)
				  break;
			}

			if (i != table[index].end()){
				table[index].erase(i);
				deleted = 1;
			}
			return deleted;
	    }
	 
	    int hashFunction(string str) {
	    	int x = 0;
	    	transform(str.begin(), str.end(), str.begin(), ::tolower);

	    	for (int i = 0; str[i]; ++i)
	    	{
	    		x = (x + str[i])%this->BUCKET;
	    	}
	        return x;
	    }
	 	
		void displayHash() {
			for (int i = 0; i < BUCKET; i++) {
			cout << i;
			for (auto x : table[i])
			  cout << " --> " << x;
			cout << endl;
			}
		}
};



class Vocabulary{
	public:
		std::vector<Vocab> vocabs;
		Hash hs = Hash(50);

		Vocabulary(){
			loadVocabsFromFile();
			//this->hs.displayHash();
		}
		Vocabulary(std::vector<Vocab> _vocabs){
			this->vocabs = _vocabs;
		}

		void addVocab(Vocab _vocab){
			this->vocabs.push_back(_vocab);
			this->hs.insertItem(_vocab.getWord(), totalVocab);
			totalVocab++;
		}

		int findVocab(string _word){
			int idx = -1;
			if(this->vocabs.empty()){
				std::cout << "Empty Vocabulary." << endl;
			}
			int key = this->hs.hashFunction(_word);
			list <int> :: iterator i;
			for (i = this->hs.table[key].begin(); i != this->hs.table[key].end(); i++) {
				if(strcasecmp(_word.c_str(), this->vocabs[*i].getWord().c_str())==0){
				  	idx = (*i);
		     		return idx;
		     	}
			}

			if (i == this->hs.table[key].end()){
				std::cout << "Could not find vocab with \"" << _word << "\"" << endl;
			}
			return idx;
		}

		int deleteVocab(string _word){
			int deleted = 0;
			if(this->vocabs.empty()){
				std::cout << "Empty Vocabulary." << endl;
				return deleted;
			}

			int idx = findVocab(_word);

			if(idx!=-1){
				this->vocabs.erase(this->vocabs.begin() + idx);
	    		this->hs.deleteItem(_word, idx);
	    		deleted = 1;
	    		std::cout << "Vocab deleted." << endl;
			}

		    if(deleted == 0) std::cout << "Could not find vocab with \"" << _word << "\"" << endl;
		    return deleted;
		}

		void showAllVocabs(){
			std::vector<Vocab>::iterator it;
			int count = 0;
			if(this->vocabs.empty()){
				std::cout << "Empty Vocabulary." << endl;
				return;
			}
			for(it = this->vocabs.begin(); it!=this->vocabs.end(); it++){
				count++;
				if(count == 1) std::cout << "All vocabs:" << endl;
		    	std::cout << count << ": " << (*it).getWord() << endl;
		    }
		}

		vector<string> split(string s, string delimiter) {
		    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		    string token;
		    vector<string> res;

		    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
		        token = s.substr (pos_start, pos_end - pos_start);
		        pos_start = pos_end + delim_len;
		        res.push_back (token);
		    }

		    res.push_back (s.substr (pos_start));
		    return res;
		}

		std::tm stringToTm(string datestr){
			int year;
			int month;
			int day;
			char ws;
			string yearstr, daystr, monthstr;
   			vector<string> v = split(datestr, ".");

   			int count = 0;
    		for (auto i : v) {
    			count++;
    			if(count == 1)day = std::stoi(i);
    			else if(count == 2)month = std::stoi(i);
    			else if(count == 3)year = std::stoi(i);
    		}

			std::tm bar = { 0, 0, 0, day, month - 1, year - 1900 };
			return bar;
		}

		int loadVocabsFromFile(){

			std::ifstream data_file(VOCABULARY_FILE);
			string _word, _meaning, _example, line;
			std::vector<string> _example_sentences;
			std::tm _date_added, _date_last_reviewed;
			int _nExample, _level;

		    if (!data_file.is_open()) {
		        std::cout << "Could not open the file - '"
		             << VOCABULARY_FILE << "'" << endl;
		        return 0;
		    }

		    int count = 0, ex_count = 0, idx = 0;
		    while (getline(data_file, line)){
		        switch(count){
		        	case 0:
		        		_word = line;
		        		count++;
		        		break;
		        	case 1:
		        		_level = line[0] - '0';
		        		count++;
		        		break;
		        	case 2:
		        		_meaning = line;
		        		count++;
		        		break;
		        	case 3:
		        		_date_added = stringToTm(line);
		        		count++;
		        		break;
		        	case 4:
		        		_date_last_reviewed = stringToTm(line);
		        		count++;
		        		break;
		        	case 5:
		        		_nExample = line[0] - '0';
		        		ex_count = 0;
		        		_example_sentences.clear();
		        		if(_nExample == 0){
		        			Vocab vocab(_word, _level, _meaning, _date_added, _date_last_reviewed, _nExample, _example_sentences);
			        		this->vocabs.push_back(vocab);
			        		this->hs.insertItem(_word, idx);
			        		idx++;
			        		totalVocab++;
			        		count = 0;
		        		}
		        		else count++;
		        		break;
		        	case 6:
		        		if(ex_count < _nExample){
		        			ex_count++;
		        			_example_sentences.push_back(line);
		        		}
		        		if(ex_count == _nExample){
			        		Vocab vocab(_word, _level, _meaning, _date_added, _date_last_reviewed, _nExample, _example_sentences);
			        		this->vocabs.push_back(vocab);
			        		this->hs.insertItem(_word, idx);
			        		idx++;
			        		totalVocab++;
			        		count = 0;
			        	}
		        		break;
		        }

		    }
			data_file.close();
			return 1;
		}

		int saveVocabsToFile(){
			std::ofstream data_file(VOCABULARY_FILE);

			if (!data_file.is_open()) {
		        std::cout << "Could not open the file - '"
		             << VOCABULARY_FILE << "'" << endl;
		        return 0;
		    }

		    for(std::vector<Vocab>::iterator it = this->vocabs.begin(); it!=this->vocabs.end(); it++){
		    	Vocab vocab = *it;
		    	data_file 	<< vocab.getWord() << '\n'
		    				<< vocab.getLevel() << '\n'
		    				<< vocab.getMeaning() << '\n';

		    	std::tm n = vocab.getDateAdded();
		    	get_time(&n, "%d.%m.%Y");
		    	data_file 	<< (&n)->tm_mday << '.' << (&n)->tm_mon + 1 << '.' << (&n)->tm_year + 1900 << '\n';

		    	n = vocab.getDateLastReviewed();
		    	get_time(&n, "%d.%m.%Y");
		    	data_file 	<< (&n)->tm_mday << '.' << (&n)->tm_mon + 1 << '.' << (&n)->tm_year + 1900 << '\n'
		    				<< vocab.getNExample() << '\n';

		    	std::vector<string> _example_sentences = vocab.getExampleSentences();
    			std::vector<string>::iterator it2;
		    	for(it2 = _example_sentences.begin(); it2!=_example_sentences.end(); it2++){
		    		data_file << *it2 << '\n';
		    	}	    				

		    }
		    return 1;
		}

		int isReviewable(std::tm _date_last_reviewed, int _level){
			int isAble = 0;
			// Set current local datetime
			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);
			std::tm _date_today = *now;

			get_time(&_date_last_reviewed, "%d.%m.%Y");
			get_time(&_date_today, "%d.%m.%Y");

			int yd = (&_date_today)->tm_year - (&_date_last_reviewed)->tm_year;
			int md = (&_date_today)->tm_mon - (&_date_last_reviewed)->tm_mon;
			int dd = (&_date_today)->tm_mday - (&_date_last_reviewed)->tm_mday;

			switch(_level){
				case 1:
					if(dd>0)isAble = 1;
					break;
				case 2:
					if(dd>2)isAble = 1;
					break;
				case 3:
					if(dd>6)isAble = 1;
					break;
				case 4:
					if(dd>14)isAble = 1;
					break;
			}
			return isAble;
		}

		void getVocabsToReview(int vocabsToReviewIdx[]){
			int idx = 0, count = 0;	
			std::vector<Vocab>::iterator it;
			int eligible = 0;

			if(vocabs.empty()){
				std::cout << "Empty Vocabulary." << endl;
			}
			for(it = this->vocabs.begin(); it!=this->vocabs.end(); it++){
				if(idx == REVIEW_COUNT)break;
				eligible = 0;
		    	eligible = isReviewable((*it).getDateLastReviewed(), (*it).getLevel());
		    	if(eligible){
		    		vocabsToReviewIdx[idx] = count;
		    		idx++;
		    	}
		    	count++;
		    }
		}

		void reviewVocab(int idx){
			Vocab &vocab = this->vocabs[idx];
			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);
			std::tm _date_today = *now;
			get_time(&_date_today, "%d.%m.%Y");

			std::cout << "Vocab to review: " << vocab.getWord() << endl;
			std::cout << "Press Enter to reveal." << endl;

			string ws;
			getline(cin, ws);
			getline(cin, ws);

			vocab.displayVocabSummary();

			std::cout << "\n\n1. I know this one for sure\n2. I can not remember this one\n3. I am not sure about this one\nYour choice: ";
			
			int choice;
			std::cin >> choice;

			vocab.setDateLastReviewed(_date_today);

			switch(choice){
				case 1:
					std::cout << "Congratulation. This vocab goes up by one level.\n";
					vocab.setLevel(vocab.getLevel()+1);
					std::cout << left << setw(20) << "New level: " << vocab.getLevel() << '\n';
					break;
				case 2:
					std::cout << "Poor thing. This vocab goes down to level 1.\n";
					vocab.setLevel(1);
					std::cout << left << setw(20) << "New level: " << vocab.getLevel() << '\n';
					break;
				case 3:
					if(vocab.getLevel() != 1){
						std::cout << "Sorry. Next time try with confidence. Your lack of confidence got this vocab down by one level.\n";
						vocab.setLevel(vocab.getLevel()-1);
						std::cout << left << setw(20) << "New level: " << vocab.getLevel() << '\n';
					}
					else std::cout << "Don't worry. Level of this vocab is 1. Try next time WITH CONFIDENCE." << endl;
					break;
			}
		}

		int doReview(){
			int modified = 0;
			int vocabsToReviewIdx[REVIEW_COUNT];
			for (int i = 0; i < REVIEW_COUNT; ++i)
			{
				vocabsToReviewIdx[i] = -1;
			}

			getVocabsToReview(vocabsToReviewIdx);

			if(vocabs.empty()){
				std::cout << "Empty Vocabulary." << endl;
				return modified;
			}
			for (int i = 0; i < REVIEW_COUNT; ++i)
			{
				if(vocabsToReviewIdx[i]!=-1){
					modified |= 1;
					reviewVocab(vocabsToReviewIdx[i]);
				}
			}

			if(modified == 0)std::cout << "Nothing to review." << endl;
			else std::cout << "Review done." << endl;
			return modified;
		}

}vocabulary;

Vocab inputWord(){
	string _word, _meaning, _example, ws;
	std::vector<string> _example_sentences;
	int _nExample = -1;
	std::cout 	<< "Enter the word: ";
	std::cin 	>> _word; 

	std::cout 	<< "Enter the meaning(s) of the word: ";
	getline(cin, ws);
	getline(cin, _meaning);

	std::cout 	<< "Enter the number of example sentences(0-9): ";
	std::cin 	>> _nExample;
	
	int inc, count = 0;
	while(count < _nExample){
		count++;
		std::cout 	<< "Enter the " << count << ((count==1)?"st":(count==2)?"nd":(count==3)?"rd":"th") << " example sentence: ";
		getline(cin, ws);
		getline(cin, _example);
		std::cout 	<< "Okay?(0/1)\n";
		std::cin 	>> inc;
		if(inc == 1)
			_example_sentences.push_back(_example);
		else
			count--;
	}

	Vocab vocab(_word, _meaning, _nExample, _example_sentences);
	return vocab;
}




void reset_level(std::vector<Vocab> &vocabs){
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	std::tm _date_today = *now;
	get_time(&_date_today, "%d.%m.%Y");

	for(std::vector<Vocab>::iterator it = vocabs.begin(); it!=vocabs.end(); it++){
		std::tm _date_last_reviewed = (*it).getDateLastReviewed();
		int _level = (*it).getLevel();
		get_time(&_date_last_reviewed, "%d.%m.%Y");

		int yd = (&_date_today)->tm_year - (&_date_last_reviewed)->tm_year;
		int md = (&_date_today)->tm_mon - (&_date_last_reviewed)->tm_mon;
		int dd = (&_date_today)->tm_mday - (&_date_last_reviewed)->tm_mday;

		switch(_level){
			case 2:
				if(dd>1)(*it).setLevel(1);
				break;
			case 3:
				if(dd>3)(*it).setLevel(2);
				break;
			case 4:
				if(dd>7)(*it).setLevel(3);
				break;
		}
	}
}


int main(int argc, char const *argv[])
{

    int choice, inc, modified = 0, isDeleted = 0, idx;
    Vocab vocab;
	string _wd;    

    while(1){

	    std::cout 	<< "*----------Give yourself credit for at least ending up here---------------*\n"
	    			<< "*---------------------Continue preparing for GRE--------------------------*\n"
	    			<< "*-----------------------Improve your vocabulary---------------------------*\n"
	    			<< "*--------------------------------Menu-------------------------------------*\n"
	    			<< "*                                                                         *\n"
	    			<< "*                      1. Insert new word                                 *\n"
	    			<< "*                      2. Delete existing word                            *\n"
	    			<< "*                      3. Review words                                    *\n"
	    			<< "*                      4. Show all vocabs                                 *\n"
	    			<< "*                      5. Find vocab                                      *\n"
	    			<< "*                      0. Exit                                            *\n"
	    			<< "*                                                                         *\n"
	    			<< "*----------------------------Give choice----------------------------------*\n\n"
	    			<< "Your choice: ";

    	std::cin >> choice;
		switch(choice){
	    	case 1:
		    	vocab = inputWord();
		    	vocab.displayVocabSummary();
		    	std::cout << "Save?(0/1)";
		    	std::cin  >> inc;
		    	if(inc == 1){
		    		vocabulary.addVocab(vocab);
		    		modified = 1;
		    	}
		    	break;
		    case 2:
		    	std::cout << "Give the word to delete: ";
		    	std::cin >> _wd;

		    	isDeleted = vocabulary.deleteVocab(_wd);
				if(isDeleted == 0)std::cout << "Vocab not deleted." << endl;
				modified |= isDeleted;
		    	break;
		    case 3:
		    	modified |= vocabulary.doReview();
		    	break;
		    case 4:
		    	vocabulary.showAllVocabs();
		    	break;
		    case 5:	    	
		    	std::cout << "Give the word to find: ";
		    	std::cin >> _wd;
		    	idx = vocabulary.findVocab(_wd);
		    	if(idx!=-1)vocabulary.vocabs[idx].displayVocabSummary();
		    	break;
	    	case 0:
	    		if(modified){
					std::cout << "Saving modified vocabs in the file. DO NOT STOP THE PROGRAM!!!....\n";
					vocabulary.saveVocabsToFile();
					std::cout << "Saved modified vocabs in the file successfully.\n";
				}
				std::cout << "Come again soon for your own good!!!\n";
				return 0;
	    }
    }

	return 0;
}