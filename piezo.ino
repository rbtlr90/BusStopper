const int buzzerPin =A3;

// Length must equal the total number of notes and spaces 
const int songLength = 1;

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)
char notes[] = "a"; // a space represents a rest

// Beats is an array of values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.
int beats[] = {2};

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.
int tempo = 500;

void setup() 
{
  pinMode(buzzerPin, OUTPUT);
}

void loop() 
{
  
    tone(buzzerPin, 392, 500);
    
    delay(1000-(2000/distance));   //delay gets shorter as distance gets closer
  }

  // We only want to play the song once, so we'll pause forever:
  while(true){}
  // If you'd like your song to play over and over,
  // remove the above statement
}


int frequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.

  int i;
  const int numNotes = 8;  // number of notes we're storing

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}
