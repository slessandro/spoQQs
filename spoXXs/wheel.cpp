#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>

#include <wheel_define.h>

#include <wheel.h>
#include <wheelbuild.h>



wheel::Wheel::Wheel()
{
    isFirstRun = true;
    isScreenOutput_ = false;
    isFileOutput_ = false;


    input_ = "";
    output_ = "";


    isFront = true;
    iHoles  = 24;
    iHolesL = 12;
    iHolesR = 12;
    blockL = 1;
    schemeL[0] = 0;
    schemeL[1] = 0;
    schemeL[2] = 0;
    schemeL[3] = 0;
    schemeL[4] = 0;
    schemeL[5] = 0;
    schemeL[6] = 0;
    schemeL[7] = 0;
    schemeL[8] = 0;
    schemeL[9] = 0;
    blockR = 1;
    schemeR[0] = 0;
    schemeR[1] = 0;
    schemeR[2] = 0;
    schemeR[3] = 0;
    schemeR[4] = 0;
    schemeR[5] = 0;
    schemeR[6] = 0;
    schemeR[7] = 0;
    schemeR[8] = 0;
    schemeR[9] = 0;



    hub.label = "hub";
    hub.isFront = isFront;
    hub.isTiltAuto = true;
    hub.flangesTilt = 0.0;
    hub.flangesTiltAuto = 0.0;

    hub.widthL = 37.9;
    hub.flangeDiameterL = 30.0;
    hub.holesDiameterL = 2.5;
    hub.holesOffsetL = 0.0;
    hub.isStraightpullL = false;
    hub.isPairedL = false;
    hub.isRadialStraightpullL = false;
    hub.isAlternativeCoupled = false;
    hub.isHeadsAlternatingL = true;
    hub.isHeadsoutL = false;

    hub.widthR = 37.9;
    hub.flangeDiameterR = 30.0;
    hub.holesDiameterR = 2.5;
    hub.holesOffsetR = 0.0;
    hub.isStraightpullR = false;
    hub.isPairedR = false;
    hub.isRadialStraightpullR = false;
    hub.isAlternativeCoupled = false;
    hub.isHeadsAlternatingR = true;
    hub.isHeadsoutR = false;

    hub.flangeThickness = 3;
    hub.old = 110.0;
    hub.weight = 100.0;



    rim.isGrouped = false;
    rim.isFront = isFront;
    rim.isGroupedAuto = true;
    rim.isSwapped = false;
    rim.holesPerGroupMan = 1;
    rim.holesPerGroupAuto = 1;
    rim.holesPerGroupShift = 0;
    rim.erd = 600.0;
    rim.osb = 0.0;
    rim.groupedHolesDistance = 0.0;
    rim.spokeBedDistance = 0.0;
    rim.weight = 0.0;
    rim.label = "rim";



    spokes.youngModulus = 200;           //  GPa
    spokes.specificVolume = 120;         //  (mm^3)/g
    spokes.forceNominal = 980;           //  N

    spokes.threadDiameterL = 2.0;
    spokes.packWeightL = 283.0;
    spokes.packLengthL = 264;
    spokes.packPcsL = 64;
    spokes.labelL = "spoke";

    spokes.threadDiameterR = 2.0;
    spokes.packWeightR = 283.0;
    spokes.packLengthR = 264;
    spokes.packPcsR = 64;
    spokes.labelR = "spoke";



    nipples.packWeightL = 26.0;
    nipples.packLengthL = 15;
    nipples.packPcsL = 64;
    nipples.labelL = "nipples left";

    nipples.packWeightR = 26.0;
    nipples.packLengthR = 15;
    nipples.packPcsR = 64;
    nipples.labelR = "nipples right";
}



void wheel::Wheel::calcMeanValues()
{
    int             holesL;
    int             holesR;

    float           tempElongation;
    float           tempForce;
    float           tempAngle;

    holesL = hub.getiHolesL();
    holesR = hub.getiHolesR();

    weightSpokes_ = 0;

    tempElongation = 0;
    tempForce = 0;
    tempAngle = 0;
    for (int i = 0 ; i < holesL ; i++ )
        {
        tempElongation = tempElongation + spokes.getSpoke(i).getElongation();
        tempForce = tempForce + spokes.getSpoke(i).getForce();
        tempAngle = tempAngle + spokes.getSpoke(i).getBracingAngle();
        weightSpokes_ = weightSpokes_ + spokes.getSpoke(i).getWeight();
        }
    meanElongationL_ = tempElongation/holesL;
    meanForceL_ = tempForce/holesL;
    meanAngleL_ = tempAngle/holesL;

    tempElongation = 0;
    tempForce = 0;
    tempAngle = 0;
    for (int i = holesL ; i < holesR+holesL ; i++ )
        {
        tempElongation = tempElongation + spokes.getSpoke(i).getElongation();
        tempForce = tempForce + spokes.getSpoke(i).getForce();
        tempAngle = tempAngle + spokes.getSpoke(i).getBracingAngle();
        weightSpokes_ = weightSpokes_ + spokes.getSpoke(i).getWeight();
        }
    meanElongationR_ = tempElongation/holesR;
    meanForceR_ = tempForce/holesR;
    meanAngleR_ = tempAngle/holesR;

    weightNipples_ = nipples.totalWeightL() + nipples.totalWeightR();
}



void wheel::Wheel::setIsScreenOutput(bool isScreenOutput)
{
    isScreenOutput_ = isScreenOutput;
}



void wheel::Wheel::setIsFileOutput(bool isFileOutput)
{
    isFileOutput_ = isFileOutput;
}



void wheel::Wheel::assessWheel(bool isFromInit , float angle)
{
    float   bracingL;
    float   bracingR;

    if (isFromInit)
        {
        hub.setFlangesParameters();
        hub.initFlanges(iHoles,iHolesL);

        iHoles  = hub.getiHoles();
        iHolesL = hub.getiHolesL();
        iHolesR = hub.getiHolesR();

        rim.holesPerGroupAuto = calcHolesPerGroupAuto(iHoles,iHolesL);
        rim.holesPerGroupAutoShift = calcHolesPerGroupAutoShift(iHoles,iHolesL);

        rim.initRim(iHoles);
        hub.flangesTiltAuto = calcHubRimRelations(hub,rim);

        rotationAnglePrev_ = 0;
        }

    rim.rotateRim(angle-rotationAnglePrev_);
    rotationAnglePrev_ = angle;

    blockL = patternL.initPattern(iHolesL,blockL);
    patternL.loadPattern(schemeL,hub.isRadialStraightpullL);

    blockR = patternR.initPattern(iHolesR,blockR);
    patternR.loadPattern(schemeR,hub.isRadialStraightpullR);

    bracingL = 0;
    if (hub.isStraightpullL || hub.isRadialStraightpullL || hub.isHeadsAlternatingL)
        bracingL = 0;
    else  if (hub.isHeadsoutL)
        bracingL = -(hub.flangeThickness+2)/2;
    else
        bracingL =  (hub.flangeThickness+2)/2;
    spokes.bracingParameterL = bracingL;
    spokes.radialOffsetL = hub.radialOffset(LEFT);

    bracingR = 0;
    if (hub.isStraightpullR || hub.isRadialStraightpullR || hub.isHeadsAlternatingR)
        bracingR = 0;
    else  if (hub.isHeadsoutR)
        bracingR = -(hub.flangeThickness+2)/2;
    else
        bracingR =  (hub.flangeThickness+2)/2;
    spokes.bracingParameterR = bracingR;
    spokes.radialOffsetR = hub.radialOffset(RIGHT);

    spokes.initSpokes(iHoles);
    populateSpokes(hub,rim,spokes,patternL,patternR);
    spokes.calcSpokes();

    nipples.calcNipples(iHoles,iHolesL);

    isFirstRun = false;
}



void wheel::Wheel::saveParameters()
{
    std::ofstream dataFile (input_.c_str());
    if (dataFile.is_open())
        {
        dataFile
        << isFront                   << ","
        << iHoles                    << ","
        << iHolesL                   << ","
        << iHolesR                   << std::endl

        << blockL                    << ","
        << schemeL[0]                << ","
        << schemeL[1]                << ","
        << schemeL[2]                << ","
        << schemeL[3]                << ","
        << schemeL[4]                << ","
        << schemeL[5]                << ","
        << schemeL[6]                << ","
        << schemeL[7]                << ","
        << schemeL[8]                << ","
        << schemeL[9]                << std::endl

        << blockR                    << ","
        << schemeR[0]                << ","
        << schemeR[1]                << ","
        << schemeR[2]                << ","
        << schemeR[3]                << ","
        << schemeR[4]                << ","
        << schemeR[5]                << ","
        << schemeR[6]                << ","
        << schemeR[7]                << ","
        << schemeR[8]                << ","
        << schemeR[9]                << std::endl



        << hub.label                 << ","
        << hub.isTiltAuto            << ","
        << hub.flangesTilt           << ","
        << hub.flangesTiltAuto       << std::endl

        << hub.widthL                << ","
        << hub.flangeDiameterL       << ","
        << hub.holesDiameterL        << ","
        << hub.holesOffsetL          << ","
        << hub.isStraightpullL       << ","
        << hub.isPairedL             << ","
        << hub.isRadialStraightpullL << ","
        << hub.isAlternativeCoupled  << ","
        << hub.isHeadsAlternatingL   << ","
        << hub.isHeadsoutL           << std::endl

        << hub.widthR                << ","
        << hub.flangeDiameterR       << ","
        << hub.holesDiameterR        << ","
        << hub.holesOffsetR          << ","
        << hub.isStraightpullR       << ","
        << hub.isPairedR             << ","
        << hub.isRadialStraightpullR << ","
        << hub.isAlternativeCoupled  << ","
        << hub.isHeadsAlternatingR   << ","
        << hub.isHeadsoutR           << std::endl

        << hub.flangeThickness       << ","
        << hub.old                   << ","
        << hub.weight                << std::endl



        << rim.label                 << ","
        << rim.isGrouped             << ","
        << rim.isGroupedAuto         << ","
        << rim.isSwapped             << ","
        << rim.holesPerGroupMan      << ","
        << rim.holesPerGroupAuto     << ","
        << rim.holesPerGroupShift    << ","
        << rim.erd                   << ","
        << rim.osb                   << ","
        << rim.groupedHolesDistance  << ","
        << rim.spokeBedDistance      << ","
        << rim.weight                << std::endl



        << spokes.youngModulus       << ","
        << spokes.specificVolume     << ","
        << spokes.forceNominal       << std::endl

        << spokes.labelL             << ","
        << spokes.threadDiameterL    << ","
        << spokes.packWeightL        << ","
        << spokes.packLengthL        << ","
        << spokes.packPcsL           << std::endl

        << spokes.labelR             << ","
        << spokes.threadDiameterR    << ","
        << spokes.packWeightR        << ","
        << spokes.packLengthR        << ","
        << spokes.packPcsR           << std::endl



        << nipples.labelL            << ","
        << nipples.packWeightL       << ","
        << nipples.packLengthL       << ","
        << nipples.packPcsL          << std::endl

        << nipples.labelR            << ","
        << nipples.packWeightR       << ","
        << nipples.packLengthR       << ","
        << nipples.packPcsR
        << std::endl;

        dataFile.close();
        }
}



void wheel::Wheel::loadParameters()
{
    int                         i = 0;
    std::vector<std::string>    result;
    std::string                 line;
    std::string                 defaultFile("spoXXs.defaults");


    if (input_ == "")
        input_ = defaultFile;

    std::ifstream dataFile (input_.c_str());
    if (dataFile.is_open())
        {
        while( std::getline(dataFile,line) )
            {
            std::stringstream ss(line);
            while( std::getline(ss,line, ',') )
                {
                i++;
                result.push_back(line);
                }
            }

        dataFile.close();
        if (i != 86) return;

        isFront                   = atof(result[0].c_str());
        iHoles                    = atof(result[1].c_str());
        iHolesL                   = atof(result[2].c_str());
        iHolesR                   = atof(result[3].c_str());
        
        blockL                    = atof(result[4].c_str());
        schemeL[0]                = atof(result[5].c_str());
        schemeL[1]                = atof(result[6].c_str());
        schemeL[2]                = atof(result[7].c_str());
        schemeL[3]                = atof(result[8].c_str());
        schemeL[4]                = atof(result[9].c_str());
        schemeL[5]                = atof(result[10].c_str());
        schemeL[6]                = atof(result[11].c_str());
        schemeL[7]                = atof(result[12].c_str());
        schemeL[8]                = atof(result[13].c_str());
        schemeL[9]                = atof(result[14].c_str());
        
        blockR                    = atof(result[15].c_str());
        schemeR[0]                = atof(result[16].c_str());
        schemeR[1]                = atof(result[17].c_str());
        schemeR[2]                = atof(result[18].c_str());
        schemeR[3]                = atof(result[19].c_str());
        schemeR[4]                = atof(result[20].c_str());
        schemeR[5]                = atof(result[21].c_str());
        schemeR[6]                = atof(result[22].c_str());
        schemeR[7]                = atof(result[23].c_str());
        schemeR[8]                = atof(result[24].c_str());
        schemeR[9]                = atof(result[25].c_str());
        
        
        
        hub.label                 = (result[26]);
        hub.isTiltAuto            = atof(result[27].c_str());
        hub.flangesTilt           = atof(result[28].c_str());
        hub.flangesTiltAuto       = atof(result[29].c_str());
        
        hub.widthL                = atof(result[30].c_str());
        hub.flangeDiameterL       = atof(result[31].c_str());
        hub.holesDiameterL        = atof(result[32].c_str());
        hub.holesOffsetL          = atof(result[33].c_str());
        hub.isStraightpullL       = atof(result[34].c_str());
        hub.isPairedL             = atof(result[35].c_str());
        hub.isRadialStraightpullL = atof(result[36].c_str());
        hub.isAlternativeCoupled  = atof(result[37].c_str());
        hub.isHeadsAlternatingL   = atof(result[38].c_str());
        hub.isHeadsoutL           = atof(result[39].c_str());
        
        hub.widthR                = atof(result[40].c_str());
        hub.flangeDiameterR       = atof(result[41].c_str());
        hub.holesDiameterR        = atof(result[42].c_str());
        hub.holesOffsetR          = atof(result[43].c_str());
        hub.isStraightpullR       = atof(result[44].c_str());
        hub.isPairedR             = atof(result[45].c_str());
        hub.isRadialStraightpullR = atof(result[46].c_str());
        hub.isAlternativeCoupled  = atof(result[47].c_str());
        hub.isHeadsAlternatingR   = atof(result[48].c_str());
        hub.isHeadsoutR           = atof(result[49].c_str());
        
        hub.flangeThickness       = atof(result[50].c_str());
        hub.old                   = atof(result[51].c_str());
        hub.weight                = atof(result[52].c_str());
        
        
        
        rim.label                 = (result[53]);
        rim.isGrouped             = atof(result[54].c_str());
        rim.isGroupedAuto         = atof(result[55].c_str());
        rim.isSwapped             = atof(result[56].c_str());
        rim.holesPerGroupMan      = atof(result[57].c_str());
        rim.holesPerGroupAuto     = atof(result[58].c_str());
        rim.holesPerGroupShift    = atof(result[59].c_str());
        rim.erd                   = atof(result[60].c_str());
        rim.osb                   = atof(result[61].c_str());
        rim.groupedHolesDistance  = atof(result[62].c_str());
        rim.spokeBedDistance      = atof(result[63].c_str());
        rim.weight                = atof(result[64].c_str());
        
        
        
        spokes.youngModulus       = atof(result[65].c_str());
        spokes.specificVolume     = atof(result[66].c_str());
        spokes.forceNominal       = atof(result[67].c_str());
        
        spokes.labelL             = (result[68]);
        spokes.threadDiameterL    = atof(result[69].c_str());
        spokes.packWeightL        = atof(result[70].c_str());
        spokes.packLengthL        = atof(result[71].c_str());
        spokes.packPcsL           = atof(result[72].c_str());
        
        spokes.labelR             = (result[73]);
        spokes.threadDiameterR    = atof(result[74].c_str());
        spokes.packWeightR        = atof(result[75].c_str());
        spokes.packLengthR        = atof(result[76].c_str());
        spokes.packPcsR           = atof(result[77].c_str());
        
        
        
        nipples.labelL            = (result[78]);
        nipples.packWeightL       = atof(result[79].c_str());
        nipples.packLengthL       = atof(result[80].c_str());
        nipples.packPcsL          = atof(result[81].c_str());
        
        nipples.labelR            = (result[82]);
        nipples.packWeightR       = atof(result[83].c_str());
        nipples.packLengthR       = atof(result[84].c_str());
        nipples.packPcsR          = atof(result[85].c_str());
        }
}



void wheel::Wheel::outputToScreen()
{
    float pi = 3.1415927;


    if (!isScreenOutput_) return;

    std::cout
    << std::setw(8)   << "hub"
    << std::setw(8)   << "angle"
    << std::setw(8)   << "rim"
    << std::setw(8)   << "angle"
    << std::setw(12)  << "length"
    << std::setw(8)   << "brace"
    << std::setw(8)   << "cross"
    << std::setw(8)   << "ratio"
    << std::setw(8)   << "elong"
    << std::endl;

    for (int i = 0 ; i < iHoles ; i++ )
    {
        char lr;
        (spokes.getSpoke(i).flange) ? lr = 'R' : lr = 'L';
        std::cout
        << std::fixed    << std::setprecision(2)
        << std::setw(6)  << spokes.getSpoke(i).nHub
        << std::setw(2)  << lr
        << std::setw(8)  << spokes.getSpoke(i).angleHub*(180.0/pi)
        << std::setw(8)  << spokes.getSpoke(i).nRim
        << std::setw(8)  << spokes.getSpoke(i).angleRim*(180.0/pi)
        << std::setw(12) << spokes.getSpoke(i).getLength()
        << std::setw(8)  << spokes.getSpoke(i).getBracingAngle()
        << std::setw(8)  << spokes.getSpoke(i).getRealXcross()
        << std::setw(8)  << spokes.getSpoke(i).getRatio()
        << std::setw(8)  << spokes.getSpoke(i).getElongation()
        << std::endl;
    }
}



void wheel::Wheel::outputToFile()
{
    float pi = 3.1415927;


    if (!isFileOutput_) return;

    std::ofstream outputFile (output_.c_str());
    if (outputFile.is_open())
        {
        outputFile
        << std::setw(8)   << "hub,"
        << std::setw(8)   << "angle,"
        << std::setw(8)   << "rim,"
        << std::setw(8)   << "angle,"
        << std::setw(12)  << "length,"
        << std::setw(8)   << "brace,"
        << std::setw(8)   << "cross,"
        << std::setw(8)   << "ratio,"
        << std::setw(8)   << "elong "
        << std::endl;
      
        for (int i = 0 ; i < iHoles ; i++ )
            {
            char lr;
            (spokes.getSpoke(i).flange) ? lr = 'R' : lr = 'L';
            outputFile
            << std::fixed    << std::setprecision(2)
            << std::setw(5)  << spokes.getSpoke(i).nHub                 << ","
            << std::setw(1)  << lr                                      << ","
            << std::setw(7)  << spokes.getSpoke(i).angleHub*(180.0/pi)  << ","
            << std::setw(7)  << spokes.getSpoke(i).nRim                 << ","
            << std::setw(7)  << spokes.getSpoke(i).angleRim*(180.0/pi)  << ","
            << std::setw(11) << spokes.getSpoke(i).getLength()          << ","
            << std::setw(7)  << spokes.getSpoke(i).getBracingAngle()    << ","
            << std::setw(7)  << spokes.getSpoke(i).getRealXcross()      << ","
            << std::setw(7)  << spokes.getSpoke(i).getRatio()           << ","
            << std::setw(7)  << spokes.getSpoke(i).getElongation()
            << std::endl;
            }

        outputFile.close();
        }
}



int wheel::Wheel::commandLine(int argC , char* argV[])
{
    int                         error;
    int                         token;
    std::vector <std::string>   commands;


    for (int i = 0 ; i < argC ; i++)
        commands.push_back(std::string(argV[i]));

    token = 0;
    error = 0;
    isFileOutput_ = false;
    isScreenOutput_ = false;
    for (int i = 1 ; i < argC ; i++)
        {
        if (!error)
            {
            if      ( commands[i] == "-i" )
                {
                if ((i == (argC-1)) || (argV[i+1][0] == '-'))
                    {
                    error = 1;
                    }
                else
                    {
                    std::ifstream file (commands[i+1].c_str());
                    if (file.is_open())
                        {
                        file.close();
                        input_ = commands[i+1];
                        }
                    else
                        {
                        error = 2;
                        }
                    }
                i++;
                }

            else if ( commands[i] == "-o" )
                {
                if ((i == (argC-1)) || (argV[i+1][0] == '-'))
                    {
                    error = 3;
                    }
                else
                    {
                    std::ifstream file (commands[i+1].c_str());
                    if (file.is_open())
                        {
                        file.close();
                        error = 4;
                        }
                    else
                        {
                        output_ = commands[i+1];
                        isFileOutput_ = true;
                        }
                    }
                i++;
                }

            else if ( commands[i] == "-s" )
                {
                isScreenOutput_ = true;
                }

            else if ( commands[i] == "-h" )
                {
                error = 100;
                }

            else
                {
                token = i;
                error = 5;
                }
            }
        }

    switch (error)
        {
        case 1 :
        std::cout << "Error: input file missing." << std::endl;
        break;

        case 2 :
        std::cout << "Error: cannot open input file." << std::endl;
        break;

        case 3 :
        std::cout << "Error: output file missing." << std::endl;
        break;

        case 4 :
        std::cout << "Error: output file already exists." << std::endl;
        break;

        case 5 :
        std::cout << "Error: option <" << commands[token] << "> not recognized." << std::endl;
        break;

        case 100 :
        std::cout << std::endl;
        std::cout << " -i <input file>    input file." << std::endl;
        std::cout << " -o <output file>   output file" << std::endl;
        std::cout << " -s                 output to screen" << std::endl;
        std::cout << " -h                 available options list" << std::endl << std::endl;
        std::cout << " If input file is not specified, <spoXXs.defaults> will be opened." << std::endl;
        std::cout << " If <spoXXs.defaults> doesn't exist a new file <spoXXs.defaults> containig default data will be generated." << std::endl;
        std::cout << " <input file> is always overwritten (erroneus data will be corrected or, if incoplete, will be filled with default data)." << std::endl << std::endl;
        break;
        }

    return error;
}
