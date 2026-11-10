#ifndef XOBJECTTYPE_H
#define XOBJECTTYPE_H

enum EXObjectType
{
	EXBegin =				0,
	EXNullType	=			1,
	// system preserved [0, 100)

	EXProject				= 100,	
	EXPointsFolder			= 1000,
	EXWellFolder			= 1100,	
	EXWellCurveAliasFolder = 1150,
	EXFaultFolder = 1200,
	EXFaultPolygonFolder = 1250,
	EXSurfaceFolder = 1300,
	EXHorizonFolder = 1350,
	EXPolygonFolder = 1400,
	EXWaveletFolder = 1500,
	EXSeismicDVFolder = 1600,
	EXSeismicGatherFolder = 1610,
	EXSeismicSectionFolder = 1650,
	EXSeismicDataLineFolder = 1660,
	EXGeobodyFolder = 1700,
	EXLFMFolder			= 1800,
	EXLFMUpscalingResultFolder	= 1900,
	EXLFMAttributeFolder = 2000,
	EX3TermAVOInversionFolder = 2100,
	EXNMRFolder = 2200,
	EXFractureAnalysisAVO	= 2300,
	EXHorizonAttributeFolder = 2400,
	EXFractureInversionFolder = 2500,
	EXAnisotropyForwardingFolder = 2600,
	EXFracturePatchFolder = 2700,

	// Project preserved [100, 1,000)

	//	Well relevant objects.
	EXWell					= 10000,
	EXWellPath				= 12000,
	EXWellCurve			= 13000,
	EXWellCurveAlias = 13100,
	EXWellCompData = 15000,
	EXWellComp = 15001,
	EXWellTops = 16000,
	EXWellTopFormation = 16100,
	EXWellZones = 16200,
	EXWellTD = 17000,
	EXWellNMR = 17100,

	// wavelet
	EXWavelet              = 18000,

	//	Line/polygon relevant objects.
	EXFaultPolygon			= 20000,
	EXFaultSticks			= 21000,
	EX2DPolygon			= 22000,

	//	Points relevant objects.
	EX3DPoints				= 30000,

	// 3-D surface, 3-D horizon
	EX3DSurface			= 40000,
	EX3DHorizon			= 41000,
	EX3DSurfaceAtt 		= 42000,
	EX3DHorizonAtt			= 43000,

	//	Followed objects used for view purpose.
	EXWellTrack			= 50000,
	EXFillCurve			= 51000,

	// Seismic data volume
	EXSeismicDataVolume	= 60000,
	EXAzimuthDataVolume	= 60500,
	EX3DSurvey				= 61000,
	EXSeismicSection		= 62000,
	EXSeismicSubVolume		= 63000,
	EXRandomSection		= 64000,

	EXPrestackGather	= 65000,

	EX2DSurvey				= 66000,
	EX2DSeismicLine		= 66100,
	EXSeismicDataLine		= 66200,
	EX2DHorizonFolder		= 66500,
	EX2DHorizon			= 66510,

	// Geobody
	EXGeobodyCollection	= 67000,
	EXGeobody				= 68000,

	// MicroSeismic data
	EXMicroSeismicData		= 70000,	

	//	Special for GSM
	EXGSGeologicStage		= 75000,
	EXGSSection				= 75100,
	EXGS3DHorizonTWT		= 75200,
	EXGS3DHorizonDepth		= 75210,
	EXGS3DHorizonIso		= 75220,
	EXGS3DHorizonAtt		= 75230,
	EXGSAnticline			= 75300,
	EXGSStructure			= 75310,
	EXGSStressMap			= 75320,
	EXGSRoseDiagram			= 75330,

	EXGSFolder				= 75400,
	EXGSFolderHorizon		= 75410,
	EXGSFolderSection		= 75420,
	EXGSFolderPDG			= 75430,
	EXGSFolderStage			= 75440,

	EXGSFaultTraces			= 75500,
	EXGSPDG					= 75510,
	EXGSFRG					= 75520,
	EXGSWellTops			= 75530,

	//	Reservoir model
	EXReservoirModel		= 80000,
	EXGridModel			= 81000,
	EXPropertyModel		= 82000,
	EXIntersectionGrid		= 82100,
	EXWellCondition		= 83000,
	EXWellCells			= 83100,
	EXCurveCells			= 83200,
	EXWellCurveCells		= 83300,

	EXFracturePatch			= 84000,

	// Geological model
	EXGM					= 90000,
	EXGMFaultFolder		= 91000,
	EXGMFault				= 92000,

	// Low frequency model
	EXLowFrequencyModel	= 95000,
	EXLFMAttribute			= 95100,
	EXLFMUpscalingGeometry	= 95200,
	EXLFMUpscalingAttribute= 95300,


	// Parameter preserved [100,000, 1,000,000)
	EMake2DGRid 			= 100000,  // 100,000
	EWellHorizonIntersect	= 110000,
	ETraceToSlice			= 200000,
	ETraceToBrick			= 210000,
	EModelIncision			= 300000,
	EMakePropertyModel      = 400000,
	EDetectGeobody			= 500000,

	EBuildLowFreuqencyModel = 600000,
	EIntersectLFMAndWell	= 610000,
	ECalculateUpscaling		= 620000,
	ELFMInterpolation		= 630000,

	EAVOInversion			= 700000,
	ECSSInversion			= 710000,
	EAVOSSInversion			= 720000,
	EAnisotropyInversion	= 730000,
	EAnisotrpicForwarding	= 740000,	

	EGSInversion			= 750000,

	EGatherFlatting			= 800000,	
	EPartialStack			= 850000,

	// filtering
	ESeismicFiltering		= 900000,
	ESeismicPCAFiltering	= 910000,
	ESeismicInterpolation	= 920000,

	// Fracture analysis
    EFractureAnalysisAVO	= 950000,
	EFractureAttribute		= 951000,

	// extract horizon attributes
	EExtractHorizonAttribute= 960000,

	// histogram
	ERecalcHistogram		= 990000,

	// remove footprint
	ERemoveFootprint		= 1000000,

	// The end
	EXEnd					= 100000000 // 100,000,000
};


#endif // RLOBJECTTYPE_H


