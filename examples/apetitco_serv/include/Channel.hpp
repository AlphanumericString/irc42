#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>

class Channel
{
  private:
	typedef enum { // need to read doc, make these more explicit
		MODE_UNKNOWN,
		MODE_L,
		MODE_T,
		MODE_I,
	} ChanMod;

	std::string name;  // name,
	std::string topic; // topic,
	ChanMod	   mode;  // modes,
	// member list with their privileges (operator, voice, etc.),
	//   std::list -> user in the middle can leave when-ever
	//   question is list of pair? list of self defined type?
	//   idk - decision paralisis AAAAAAAAa /hj
	// channel-specific settings like user limits or keys.

  public:
	// Constructors
	Channel();
	Channel(Channel const &original); // when are we gonna use this ?!
	// Destructors
	~Channel();
	// Operator overloads
	Channel &operator=(Channel const &original);
	// Getters
	// Setters
	// Member functions
	// Exceptions
};

#endif // !CHANNEL_HPP
