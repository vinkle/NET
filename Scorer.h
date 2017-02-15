#ifndef Scorer_Included
#define Scorer_Included

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
using namespace std;
#define HITTING_THRESHOLD_SENSOR1 400
#define HITTING_THRESHOLD_SENSOR2 400

//12-12-12
struct Activity
{
	// struct definitions
	struct stationary
	{
        int startIndex, endIndex;
        string startTime, endTime;  // Time of starting and ending of the activity
        vector<pair<string, pair<int, int> > > hitting; // Hitting values in these times
        vector<pair<string, pair<double, double> > > trackingData; // Tracking Data in the stationary activity
        //vector<int> framesForTrackingFailure;
        //vector<int> framesForTrackingReinit;
        //vector<int> framesForRingHitting;
		stationary()
		{
            startIndex = -1;
            endIndex = -1;
            startTime = "";
            endTime = "";
		}
		void clear()
		{
            startIndex = -1;
            endIndex = -1;
            startTime = "";
            endTime = "";
			hitting.clear();
			trackingData.clear();
            //framesForTrackingFailure.clear();
            //framesForRingHitting.clear();
            //framesForTrackingReinit.clear();
		}
	};
	struct Picking
	{
        int startIndex, endIndex;
        string startTime, endTime;
		int from_peg;
        vector<pair<string, pair<int, int> > > hitting;
        vector<pair<string, pair<double, double> > > trackingData;
        //vector<int> framesForTrackingFailure;
        //vector<int> framesForRingHitting;
        //vector<int> framesForTrackingReinit;
		Picking()
		{
            startIndex = -1;
            endIndex = -1;
            startTime = "";
            endTime = "";
            from_peg = -1;
		}
		void clear()
		{
            startIndex = -1;
            endIndex = -1;
            startTime = "";
            endTime = "";
            from_peg = -1;
			hitting.clear();
			trackingData.clear();
            //framesForTrackingFailure.clear();
            //framesForRingHitting.clear();
            //framesForTrackingReinit.clear();
		}
	};
	struct Moving
	{
        int startIndex, endIndex;
        string startTime, endTime;
        int from_peg, to_peg;
        vector<pair<string, pair<int, int> > > hitting;
        vector<pair<string, pair<double, double> > > trackingData;
        //vector<int> framesForTrackingFailure;
        //vector<int> framesForRingHitting;
        //vector<int> framesForTrackingReinit;
		Moving()
		{
            startIndex = -1;
            endIndex = -1;
            startTime = "";
            endTime = "";
            from_peg = -1;
            to_peg = -1;
		}
		void clear()
		{
            startIndex = -1;
            endIndex = -1;
            startTime = "";
            endTime = "";
            from_peg = -1;
            to_peg = -1;
			hitting.clear();
			trackingData.clear();
            //framesForTrackingFailure.clear();
            //framesForRingHitting.clear();
            //framesForTrackingReinit.clear();
		}
	};
	string  type;
	stationary s;
	Picking p;
	Moving m;

	Activity()
	{
		type = "";
	}
	void clear()
	{
		type = "";
		s.clear();
		p.clear();
		m.clear();
	}
    void print()
    {
        if(type == "stationary")
        {
            cout << "\nActivity -> Stationary\n" << "Start-Time -> " << s.startTime << " End-Time->" << s.endTime << endl;
            cout << "Hitting Data\n";
            for(unsigned int i = 0; i <  s.hitting.size(); i++)
            {
                cout << "time->" << s.hitting[i].first << "  vals->(" << s.hitting[i].second.first << "," << s.hitting[i].second.second << ")\n";
            }
            cout << "Tracking Data\n";
            for(unsigned int i = 0; i <  s.trackingData.size(); i++)
            {
                cout << "time->" << s.trackingData[i].first << "  vals->(" << s.trackingData[i].second.first << "," << s.trackingData[i].second.second << ")\n";
            }
        }
        else if(type == "picking")
        {
            cout << "\nActivity -> Picking\n" << "Start-Time -> " << p.startTime << " End-Time->" << p.endTime << endl;
            cout << "From-Peg -> " << p.from_peg << endl;
            cout << "Hitting Data\n";
            for(unsigned int i = 0; i <  p.hitting.size(); i++)
            {
                cout << "time->" << p.hitting[i].first << "  vals->(" << p.hitting[i].second.first << "," << p.hitting[i].second.second << ")\n";
            }
            cout << "Tracking Data\n";
            for(unsigned int i = 0; i <  p.trackingData.size(); i++)
            {
                cout << "time->" << p.trackingData[i].first << "  vals->(" << p.trackingData[i].second.first << "," << p.trackingData[i].second.second << ")\n";
            }

        }
        else if(type == "moving")
        {
            cout << "\nActivity -> Moving\n" << "Start-Time -> " << m.startTime << " End-Time->" << m.endTime << endl;
            cout << "From-Peg-> " << m.from_peg <<  " To-Peg-> " << m.to_peg << endl;
            cout << "Hitting Data\n";
            for(unsigned int i = 0; i <  m.hitting.size(); i++)
            {
                cout << "time->" << m.hitting[i].first << "  vals->(" << m.hitting[i].second.first << "," << m.hitting[i].second.second << ")\n";
            }
            cout << "Tracking Data\n";
            for(unsigned int i = 0; i <  m.trackingData.size(); i++)
            {
                cout << "time->" << m.trackingData[i].first << "  vals->(" << m.trackingData[i].second.first << "," << m.trackingData[i].second.second << ")\n";
            }
        }
    }
    string write(std::ofstream &Activity_Data)
    {
        string returnStr;
        if(type == "stationary")
        {
            returnStr.append("\nActivity,Stationary\n" + string("Start-Time,") + s.startTime + "\nEnd-Time," + s.endTime);
            Activity_Data << "\nActivity:Stationary\n" << "Start-Time," << s.startTime << "\nEnd-Time," << s.endTime << endl;

            returnStr.append("Hitting-Data\n");
            Activity_Data << "Hitting-Data\n";
            for(unsigned int i = 0; i <  s.hitting.size(); i++)
            {
                returnStr.append("time," + s.hitting[i].first + ",vals," + std::to_string(s.hitting[i].second.first) + "," + std::to_string(s.hitting[i].second.second) + "\n");
                Activity_Data << "time," << s.hitting[i].first << ",vals," << s.hitting[i].second.first << "," << s.hitting[i].second.second << "\n";
            }
            returnStr.append("Tracking-Data\n");
            Activity_Data << "Tracking-Data\n";
            for(unsigned int i = 0; i <  s.trackingData.size(); i++)
            {
                returnStr.append("time," + s.trackingData[i].first + ",vals," + std::to_string(s.trackingData[i].second.first) + "," + std::to_string(s.trackingData[i].second.second) + "\n");
                Activity_Data << "time," << s.trackingData[i].first << ",vals," << s.trackingData[i].second.first << "," << s.trackingData[i].second.second << "\n";
            }
        }
        else if(type == "picking")
        {
            returnStr.append("\nActivity,Picking\n" + string("Start-Time,") + p.startTime + "\nEnd-Time," + p.endTime);
            Activity_Data << "\nActivity,Picking\n" << "Start-Time," << p.startTime << "End-Time," << p.endTime << endl;

            returnStr.append("From-Peg," + std::to_string(p.from_peg) + "\n");
            Activity_Data << "From-Peg," << p.from_peg << endl;

            returnStr.append("Hitting-Data\n");
            Activity_Data << "Hitting-Data\n";
            for(unsigned int i = 0; i <  p.hitting.size(); i++)
            {
                returnStr.append("time," + p.hitting[i].first + ",vals," + std::to_string(p.hitting[i].second.first) + "," + std::to_string(p.hitting[i].second.second) + "\n");
                Activity_Data << "time," << p.hitting[i].first << ",vals," << p.hitting[i].second.first << "," << p.hitting[i].second.second << "\n";
            }

            returnStr.append("Tracking-Data\n");
            Activity_Data << "Tracking-Data\n";
            for(unsigned int i = 0; i <  p.trackingData.size(); i++)
            {
                returnStr.append("time," + p.trackingData[i].first + ",vals," + std::to_string(p.trackingData[i].second.first) + "," + std::to_string(p.trackingData[i].second.second) + "\n");
                Activity_Data << "time," << p.trackingData[i].first << ",vals," << p.trackingData[i].second.first << "," << p.trackingData[i].second.second << "\n";
            }

        }
        else if(type == "moving")
        {
            returnStr.append("\nActivity,Moving\n" + string("Start-Time,") + m.startTime + "\nEnd-Time," + m.endTime);
            Activity_Data << "\nActivity,Moving\n" << "Start-Time," << m.startTime << "\nEnd-Time," << m.endTime << endl;

            returnStr.append("From-Peg," + std::to_string(m.from_peg) + ",To-Peg," + std::to_string(m.to_peg));
            Activity_Data << "From-Peg," << m.from_peg <<  ",To-Peg," << m.to_peg << endl;

            returnStr.append("Hitting-Data\n");
            Activity_Data << "Hitting-Data\n";
            for(unsigned int i = 0; i <  m.hitting.size(); i++)
            {
                returnStr.append("time," + m.hitting[i].first + ",vals," + std::to_string(m.hitting[i].second.first) + "," + std::to_string(m.hitting[i].second.second) + "\n");
                Activity_Data << "time," << m.hitting[i].first << ",vals," << m.hitting[i].second.first << "," << m.hitting[i].second.second << "\n";
            }
            returnStr.append("Tracking-Data\n");
            Activity_Data << "Tracking Data\n";
            for(unsigned int i = 0; i <  m.trackingData.size(); i++)
            {
                returnStr.append("time," + m.trackingData[i].first + ",vals," + std::to_string(m.trackingData[i].second.first) + "," + std::to_string(m.trackingData[i].second.second) + "\n");
                Activity_Data << "time," << m.trackingData[i].first << ",vals," << m.trackingData[i].second.first << "," << m.trackingData[i].second.second << "\n";
            }
        }
        return returnStr;
    }

    string write()
    {
        string returnStr;
        if(type == "stationary")
        {
            returnStr.append("\nActivity,Stationary\n" + string("Start-Time,") + s.startTime + "\nEnd-Time," + s.endTime);
            returnStr.append("Hitting-Data\n");
            for(unsigned int i = 0; i <  s.hitting.size(); i++)
            {
                returnStr.append("time," + s.hitting[i].first + ",vals," + std::to_string(s.hitting[i].second.first) + "," + std::to_string(s.hitting[i].second.second) + "\n");
            }
            returnStr.append("Tracking-Data\n");
            for(unsigned int i = 0; i <  s.trackingData.size(); i++)
            {
                returnStr.append("time," + s.trackingData[i].first + ",vals," + std::to_string(s.trackingData[i].second.first) + "," + std::to_string(s.trackingData[i].second.second) + "\n");
            }
        }
        else if(type == "picking")
        {
            returnStr.append("\nActivity,Picking\n" + string("Start-Time,") + p.startTime + "\nEnd-Time," + p.endTime);
            returnStr.append("From-Peg," + std::to_string(p.from_peg) + "\n");
            returnStr.append("Hitting-Data\n");
            for(unsigned int i = 0; i <  p.hitting.size(); i++)
            {
                returnStr.append("time," + p.hitting[i].first + ",vals," + std::to_string(p.hitting[i].second.first) + "," + std::to_string(p.hitting[i].second.second) + "\n");
            }
            returnStr.append("Tracking-Data\n");
            for(unsigned int i = 0; i <  p.trackingData.size(); i++)
            {
                returnStr.append("time," + p.trackingData[i].first + ",vals," + std::to_string(p.trackingData[i].second.first) + "," + std::to_string(p.trackingData[i].second.second) + "\n");
            }

        }
        else if(type == "moving")
        {
            returnStr.append("\nActivity,Moving\n" + string("Start-Time,") + m.startTime + "\nEnd-Time," + m.endTime);
            returnStr.append("From-Peg," + std::to_string(m.from_peg) + ",To-Peg," + std::to_string(m.to_peg));
            returnStr.append("Hitting-Data\n");
            for(unsigned int i = 0; i <  m.hitting.size(); i++)
            {
                returnStr.append("time," + m.hitting[i].first + ",vals," + std::to_string(m.hitting[i].second.first) + "," + std::to_string(m.hitting[i].second.second) + "\n");
            }
            returnStr.append("Tracking-Data\n");
            for(unsigned int i = 0; i <  m.trackingData.size(); i++)
            {
                returnStr.append("time," + m.trackingData[i].first + ",vals," + std::to_string(m.trackingData[i].second.first) + "," + std::to_string(m.trackingData[i].second.second) + "\n");
            }
        }
        return returnStr;
    }
};

struct Result
{
	struct Hitting
	{
        vector<pair<string, pair<int, int> > > hittingData; // Hitting values in these times
		double hittingScore;
		Hitting()
		{
			hittingScore = 0;
			hittingData.clear();
		}
		void clear()
		{
			hittingScore = 0;
			hittingData.clear();
		}
	};

	struct Grasping
	{
		vector<pair <int, int> > NoFramesPicking;
        vector<pair <int, int> > timePicking;
        vector <pair<int, vector <pair<double, double> > > > trackingData;
        vector<pair <int, double> > curvatureMax;
        vector<pair<int, double> > curvatureMaxCount;
        vector<pair<int, double> > arcLength;
		double grapspingScore;
		double grapspingTrackingScore;
		Grasping()
		{
			NoFramesPicking.clear();
			grapspingScore = 0;
			grapspingTrackingScore = 0;
		}
		void clear()
		{
			NoFramesPicking.clear();
			grapspingScore = 0;
			grapspingTrackingScore = 0;
		}
	};
	
	struct WavyMotion
	{
        vector<pair<pair<int, int>, int> > NoFramesMoving;     //               to,  from, No of frames
        vector<pair<pair<int, int>, int> > timeMoving;         //               to,  from, No of ms
        vector <pair<pair<int, int>, vector <pair<double, double> > > > trackingData; //           tracking Data

        vector<pair <pair<int, int>, double> > curvatureMax;
        vector<pair <pair<int, int>, double> > curvatureMaxCount;
        vector<pair <pair<int, int>, double> > arcLength;

		double wavyMotionScore;
		double wavyMotionTrackingScore;
		WavyMotion()
		{
			NoFramesMoving.clear();
			wavyMotionScore = 0; 
			wavyMotionTrackingScore = 0;
		}
		void clear()
		{
			NoFramesMoving.clear();
			wavyMotionScore = 0;
			wavyMotionTrackingScore = 0;
		}

	};

	struct RingHitting_wrongPlacement
	{
		vector<pair<string, int> > frameRingHitting;  // activity , frame no
		double ringHittingScore;
		RingHitting_wrongPlacement()
		{
			frameRingHitting.clear();
			ringHittingScore = 0;
		}
		void clear()
		{
			frameRingHitting.clear();
			ringHittingScore = 0;
		}
	};

	struct suddenMovement
	{
		vector<pair<string, int> > frameTrackingFailed;
		double suddenMovementScore;
		suddenMovement()
		{
			frameTrackingFailed.clear();
			suddenMovementScore = 0;
		}
		void clear()
		{
			frameTrackingFailed.clear();
			suddenMovementScore = 0;
		}
	};

	struct wrongMoves
	{
		vector<pair<int, int> > rightMoves;
		vector<pair<int, int> > wrong_moves;
		double wrongMovesScore;
		wrongMoves()
		{
			wrongMovesScore = 0;
			rightMoves.clear();
			rightMoves.push_back(make_pair(5, 8));
			rightMoves.push_back(make_pair(2, 11));
			rightMoves.push_back(make_pair(4, 7));
			rightMoves.push_back(make_pair(1, 10));
			rightMoves.push_back(make_pair(3, 6));
			rightMoves.push_back(make_pair(0, 9));

			rightMoves.push_back(make_pair(9, 2));
			rightMoves.push_back(make_pair(6, 5)); 
			rightMoves.push_back(make_pair(10, 1));
			rightMoves.push_back(make_pair(7, 4));
			rightMoves.push_back(make_pair(11, 0));
			rightMoves.push_back(make_pair(8, 3));
		}

		void clear()
		{
			wrongMovesScore = 0;
			rightMoves.clear();
			rightMoves.push_back(make_pair(5, 8));
			rightMoves.push_back(make_pair(2, 11));
			rightMoves.push_back(make_pair(4, 7));
			rightMoves.push_back(make_pair(1, 10));
			rightMoves.push_back(make_pair(3, 6));
			rightMoves.push_back(make_pair(0, 9));

			rightMoves.push_back(make_pair(9, 2));
			rightMoves.push_back(make_pair(6, 5));
			rightMoves.push_back(make_pair(10, 1));
			rightMoves.push_back(make_pair(7, 4));
			rightMoves.push_back(make_pair(11, 0));
			rightMoves.push_back(make_pair(8, 3));
		}
	};
	struct No_Activity
	{
		int no_frames;
        int time;    // time in ms
		vector<vector<pair <double, double > > > trackingData;
		double trackingScore;
		double trackingScore2;
		No_Activity()
		{
			no_frames = 0;
			trackingScore = 0;
			trackingScore2 = 0;
		}
		void clear()
		{
			no_frames = 0;
			trackingScore = 0;
			trackingScore2 = 0;
			trackingData.clear();
		}
	};


	double totalScore;
	Hitting hitting;
	Grasping grasping;
	WavyMotion wavymotion;
	RingHitting_wrongPlacement ringHItting;
	suddenMovement suddenmovement;
	wrongMoves wrongmoves;
	No_Activity noactivity;
	Result()
	{
		totalScore = 0;
	}
	void clear()
	{
		totalScore = 0;
		hitting.clear();
		grasping.clear();
		wavymotion.clear();
		ringHItting.clear();
		suddenmovement.clear();
		wrongmoves.clear();
		noactivity.clear();
	}

    void print()
    {
        cout << "Hitting\n";
        cout << "Time-stamp, Sensor-1, Sensor-2\n";

        for(int i = 0; i < hitting.hittingData.size(); i++)
        {
            cout << hitting.hittingData[i].first << "," << hitting.hittingData[i].second.first << "," << hitting.hittingData[i].second.second << endl;
        }
        //resultFile << "Result," << hitting.hittingScore;

        cout << "Grasping\n";
        cout << "from-peg, Time(Seconds), Arclength, CurvatureMax, CurvatureMaxCount\n";
        for(int i = 0; i < grasping.timePicking.size(); i++)
        {
            int from_peg = grasping.timePicking[i].first;
            double timeSec = static_cast<double>(grasping.timePicking[i].second) / 1000.0;
            double arcLength= grasping.arcLength[i].second;
            double curvemax= grasping.curvatureMax[i].second;
            double curvemaxcount= grasping.curvatureMaxCount[i].second;
            cout << from_peg << "," << timeSec << "," << arcLength << "," << curvemax << "," << curvemaxcount << endl;

        }
        //resultFile
        cout << "Wavy-Motion\n";
        cout << "from-peg, to-peg, Time(Seconds), Arclength, CurvatureMax, CurvatureMaxCount\n";
        for(int i = 0; i < wavymotion.timeMoving.size(); i++)
        {
            int from_peg = wavymotion.timeMoving[i].first.first;
            int to_peg = wavymotion.timeMoving[i].first.second;
            double timeSec = static_cast<double>(wavymotion.timeMoving[i].second) / 1000.0;
            double arcLength= wavymotion.arcLength[i].second;
            double curvemax= wavymotion.curvatureMax[i].second;
            double curvemaxcount= wavymotion.curvatureMaxCount[i].second;
            cout << from_peg<< "," << to_peg<<"," << timeSec << "," << arcLength << "," << curvemax << "," << curvemaxcount << endl;
        }
        cout << "Total time spent(Sec) in No-Actvity," << static_cast<double>(noactivity.time)/1000.0;
    }
    string write(std::ofstream &resultFile)
    {
        string returnStr;
        resultFile << "Hitting\n";
        resultFile << "Time-stamp, Sensor-1, Sensor-2\n";
        returnStr.append("Hitting\n");
        returnStr.append("Time-stamp, Sensor-1, Sensor-2\n");
        for(int i = 0; i < hitting.hittingData.size(); i++)
        {
            resultFile << hitting.hittingData[i].first << "," << hitting.hittingData[i].second.first << "," << hitting.hittingData[i].second.second << endl;
            returnStr.append(hitting.hittingData[i].first + "," + std::to_string(hitting.hittingData[i].second.first)
                             + "," + std::to_string(hitting.hittingData[i].second.second) + "\n");
        }
        //resultFile << "Result," << hitting.hittingScore;

        resultFile << "Grasping\n";
        resultFile << "from-peg, Time(Seconds), No of frames, Arclength, CurvatureMax, CurvatureMaxCount\n";
        returnStr.append("Grasping\n");
        returnStr.append("from-peg, Time(Seconds), No of frames, Arclength, CurvatureMax, CurvatureMaxCount\n");
        for(int i = 0; i < grasping.timePicking.size(); i++)
        {
            int from_peg = grasping.timePicking[i].first;
            int nof = grasping.NoFramesPicking[i].second;
            double timeSec = static_cast<double>(grasping.timePicking[i].second) / 1000.0;
            double arcLength= grasping.arcLength[i].second;
            double curvemax= grasping.curvatureMax[i].second;
            double curvemaxcount= grasping.curvatureMaxCount[i].second;
            resultFile << from_peg << "," << timeSec << "," << nof << "," << arcLength << "," << curvemax << "," << curvemaxcount << endl;
            returnStr.append(std::to_string(from_peg) + "," + std::to_string(timeSec) + "," + std::to_string(nof)  + "," + std::to_string(arcLength) +
                             "," + std::to_string(curvemax) + "," + std::to_string(curvemaxcount) + "\n");
        }
        //resultFile
        resultFile << "Wavy-Motion\n";
        resultFile << "from-peg, to-peg, Time(Seconds), No of frames, Arclength, CurvatureMax, CurvatureMaxCount\n";
        returnStr.append("Wavy-Motion\n");
        returnStr.append("from-peg, to-peg, Time(Seconds), No of frames, Arclength, CurvatureMax, CurvatureMaxCount\n");
        for(int i = 0; i < wavymotion.timeMoving.size(); i++)
        {
            int from_peg = wavymotion.timeMoving[i].first.first;
            int to_peg = wavymotion.timeMoving[i].first.second;
            int nof = wavymotion.NoFramesMoving[i].second;
            double timeSec = static_cast<double>(wavymotion.timeMoving[i].second) / 1000.0;
            double arcLength= wavymotion.arcLength[i].second;
            double curvemax= wavymotion.curvatureMax[i].second;
            double curvemaxcount= wavymotion.curvatureMaxCount[i].second;
            resultFile << from_peg<< "," << to_peg<<"," << timeSec << "," << nof << "," << arcLength << "," << curvemax << "," << curvemaxcount << endl;
            returnStr.append(std::to_string(from_peg) + "," + std::to_string(to_peg) + "," + std::to_string(timeSec) + "," + std::to_string(nof) + "," +
                             std::to_string(arcLength) + "," + std::to_string(curvemax) + "," + std::to_string(curvemaxcount) + "\n");
        }
        resultFile << "Total time spent(Sec) in No-Actvity," << static_cast<double>(noactivity.time)/1000.0;
        returnStr.append("Total time spent(Sec) in No-Actvity," + std::to_string(static_cast<double>(noactivity.time)/1000.0) + "\n");


        return returnStr;
    }

    string write()
    {
        string returnStr;
        returnStr.append("Hitting\n");
        returnStr.append("Time-stamp, Sensor-1, Sensor-2\n");
        for(int i = 0; i < hitting.hittingData.size(); i++)
        {
            returnStr.append(hitting.hittingData[i].first + "," + std::to_string(hitting.hittingData[i].second.first)
                             + "," + std::to_string(hitting.hittingData[i].second.second));
        }
        //resultFile << "Result," << hitting.hittingScore;

        returnStr.append("Grasping\n");
        returnStr.append("from-peg, Time(Seconds), Arclength, CurvatureMax, CurvatureMaxCount\n");
        for(int i = 0; i < grasping.timePicking.size(); i++)
        {
            int from_peg = grasping.timePicking[i].first;
            double timeSec = static_cast<double>(grasping.timePicking[i].second) / 1000.0;
            double arcLength= grasping.arcLength[i].second;
            double curvemax= grasping.curvatureMax[i].second;
            double curvemaxcount= grasping.curvatureMaxCount[i].second;
            returnStr.append(std::to_string(from_peg) + "," + std::to_string(timeSec) + "," + std::to_string(arcLength) +
                             "," + std::to_string(curvemax) + "," + std::to_string(curvemaxcount));
        }
        //resultFile
        returnStr.append("Wavy-Motion\n");
        returnStr.append("from-peg, to-peg, Time(Seconds), Arclength, CurvatureMax, CurvatureMaxCount\n");
        for(int i = 0; i < wavymotion.timeMoving.size(); i++)
        {
            int from_peg = wavymotion.timeMoving[i].first.first;
            int to_peg = wavymotion.timeMoving[i].first.second;
            double timeSec = static_cast<double>(wavymotion.timeMoving[i].first.second) / 1000.0;
            double arcLength= wavymotion.arcLength[i].second;
            double curvemax= wavymotion.curvatureMax[i].second;
            double curvemaxcount= wavymotion.curvatureMaxCount[i].second;
            returnStr.append(std::to_string(from_peg) + "," + std::to_string(to_peg) + "," + std::to_string(timeSec) + "," +
                             std::to_string(arcLength) + "," + std::to_string(curvemax) + "," + std::to_string(curvemaxcount));
        }
        returnStr.append("Total time spent(Sec) in No-Actvity," + std::to_string(static_cast<double>(noactivity.time)/1000.0));
        return returnStr;
    }

};

#endif
