using namespace std;

class CImage
{
public:
    CImage( vector<uint8_t> grayPixels )
    {
        m_grayPixels = grayPixels;
        // dumpPixels();
    }
    void dumpPixels()
    {
        for (int i = 0; i < m_grayPixels.size(); i++)
        {
            cout << dec << setfill('0') << setw(2) << (int) m_grayPixels[i] << endl;
        }
        cout << setfill('-') << setw(20) << endl;
    }
private:
    vector<uint8_t> m_grayPixels;
};