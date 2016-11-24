

class Timeout : public Condition {
public:
	void setTime(float time);	//seconds
	void restart();
	double getRemainingTime();

private:
	float time;
}