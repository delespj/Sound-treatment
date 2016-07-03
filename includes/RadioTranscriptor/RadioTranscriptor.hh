#ifndef RADIO_TRANSCRIPTOR__
# define RADIO_TRANSCRIPTOR__

class RadioTranscriptor {
private:
    /* data */

public:
    RadioTranscriptor ();
    virtual ~RadioTranscriptor ();

    void    decode();
    void    encode();
};

#endif /* end of include guard: RADIO_TRANSCRIPTOR__ */
