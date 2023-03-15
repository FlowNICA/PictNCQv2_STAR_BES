// C++ headers
#include <string>
#include <vector>
#include <iostream>
#include <fstream> 
#include <map>

// ROOT headers
#include "TROOT.h"
#include "TFile.h"

#if ROOT_VERSION_CODE >= ROOT_VERSION(6,0,0)
// R__LOAD_LIBRARY(./build/libDrawPicture.so)
R__LOAD_LIBRARY(./build/libDrawPicture.dylib)
#endif

void makeplotstyle();

void DrawNCQVintv2_STAR_BES(){
	
    makeplotstyle();
    TFile *fstyle = new TFile("./style.root");
    TStyle *tsty = (TStyle *)fstyle->Get("PlottingInStyle");
    tsty->cd();

    gROOT->ForceStyle();
    gStyle->SetOptStat(0);
  
    // v2 integrated of charged hadrons as a function of beam energy
    // beam energies:      3   7.7    11.5    14.5    19.6       27      39     54.4     64.4  GeV
    const float v2int[] = {1, 0.044, 0.0477, 0.0483, 0.05081, 0.05199, 0.0537, 0.05575, 0.0545};

    //TString particle[]={"#pi^{+}","K^{+}","p"};
    TString particle[]={"#pi","K","p"};
	  TString Anti_particle[]={"#pi^{-}","K^{-}","#bar{p}"};

    TFile *fileIn1 = new TFile("./PublushedDataBES1.root","read");
    TFile *fileIn2 = new TFile("./HEPData-ins1897294-v1-root.root","read");
    
    std::vector<float> mass = {0.13957061,0.493677,0.9382720813};
    std::vector<int>   nq   = {2,2,3};

    std::vector<int>     MaskEnergy_File1 = {7,11,14,19,39,62};
    std::vector<TString> MaskEnergyTxt_File1 = {"7.7","11.5","14.5","19.6","39","62.4"};
    std::vector<TString> MaskParticle_File1 = {"Pion","Kaon","Proton"};
    std::vector<TString> MaskChargeParticle_File1 = {"Pos","Neg"};
    std::vector<TString> MaskCentrality_File1 = {"10_40"};
  
    std::vector<int>     MaskEnergy_File2 = {3,27,54};
    std::vector<TString> MaskEnergyTxt_File2 = {"3","27","54.4"};
    std::vector<TString> MaskParticle_File2 = {"pi","K","p"};
    std::vector<TString> MaskChargeParticle_File2 = {"a","b"};
    std::vector<TString> MaskCentrality_File2 = {""};

    Int_t color[]   =   {38,1,42,6,4,8,28,15,2};
    Int_t style[]   =   {22,24,28};
    Float_t size[]  =   {2., 2., 2.};

    Float_t AxisXmin = -0.1;
    Float_t AxisXmax = 1.64;
    Float_t AxisYmin = -0.29;
    Float_t AxisYmax = 1.99;

    std::vector<MyDrawObject *> drawOdj;
    int energyId = 0;

    // // Точки из второго файла 3 GeV уже NCQ
    // for(Int_t iEne=0; iEne<1; iEne++){    
    //   energyId = 0;
    //     for(Int_t pid=0; pid<3; pid++){  
    //         fileIn2->cd();
            
    //         // charge > 0
    //         drawOdj.push_back(new MyDrawObject());
    //         drawOdj.back()->SetMarkerColor(color[6+iEne]);
    //         drawOdj.back()->SetMarkerStyle(style[pid]);
    //         drawOdj.back()->SetMarkerSize(size[pid]);
    //         drawOdj.back()->SetNumberPadDraw(0);
    //         drawOdj.back()->SetNameGraph(Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[0].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()));
    //         drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn2->Get( Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[0].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()) ) );
    //         drawOdj.back()->VnIntScaling(v2int[energyId]); 
    //         drawOdj.back()->SetLegendText(Form("#font[42]{ #scale[1.0]{%s, %s}}",particle[pid].Data(),MaskEnergyTxt_File2[iEne].Data()));
    //         if(iEne==0 && pid==0)drawOdj.back()->SetLegendText(Form("#font[42]{ #scale[1.0]{%s, %s (GeV)}}",particle[pid].Data(),MaskEnergyTxt_File2[iEne].Data()));
        
    //         // charge < 0
    //         drawOdj.push_back(new MyDrawObject());
    //         drawOdj.back()->SetMarkerColor(color[6+iEne]);
    //         drawOdj.back()->SetMarkerStyle(style[pid]);
    //         drawOdj.back()->SetMarkerSize(size[pid]);
    //         drawOdj.back()->SetNumberPadDraw(1);
    //         drawOdj.back()->SetNameGraph(Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[1].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()));
    //         drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn2->Get( Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[1].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()) ) );        
    //         drawOdj.back()->VnIntScaling(v2int[energyId]); 
    //     }
    // }

    // Точки из первого файла BES-1, 7,11,14,19, требуется скейлинг
    for(Int_t iEne=0; iEne<4; iEne++){    
      if (iEne==0) energyId = 1;
      if (iEne==1) energyId = 2;
      if (iEne==2) energyId = 3;
      if (iEne==3) energyId = 4;
        if (iEne == 0) continue;
        // if (iEne == 1) continue;
        // if (iEne == 2) continue;
        // if (iEne == 3) continue;
        for(Int_t pid=0; pid<3; pid++){  
            
            // charge > 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(0);
            drawOdj.back()->SetNameGraph(Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[0].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn1->Get( Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[0].Data()) ) );
            drawOdj.back()->NCQScaling(nq[pid],mass[pid]); // скейлинг точек ( (sqrt(pt^2+mass^2)-mass)/nq ; v2/nq )
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
            drawOdj.back()->RemoveBigErrors(0.05, 0.5, 2);
            
            // текст легенды
            drawOdj.back()->SetLegendText(Form("#font[42]{ #scale[1.0]{%s, %s}}",particle[pid].Data(),MaskEnergyTxt_File1[iEne].Data()));
            
           // charge < 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(1);
            drawOdj.back()->SetNameGraph(Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[1].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn1->Get( Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[1].Data()) ) );
            drawOdj.back()->NCQScaling(nq[pid],mass[pid]); // скейлинг точек ( (sqrt(pt^2+mass^2)-mass)/nq ; v2/nq )
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
            drawOdj.back()->RemoveBigErrors(0.05, 0.5, 2);
        }
    }

    // Точки из второго файла 27 GeV уже NCQ
    for(Int_t iEne=1; iEne<2; iEne++){  
      energyId = 5;  
        for(Int_t pid=0; pid<3; pid++){  
            fileIn2->cd();
            
            // charge > 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[6+iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(0);
            drawOdj.back()->SetNameGraph(Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[0].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn2->Get( Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[0].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()) ) );
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
            drawOdj.back()->SetLegendText(Form("#font[42]{ #scale[1.0]{%s, %s}}",particle[pid].Data(),MaskEnergyTxt_File2[iEne].Data()));
        
            // charge < 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[6+iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(1);
            drawOdj.back()->SetNameGraph(Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[1].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn2->Get( Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[1].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()) ) );        
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
        }
    }

    // Точки из первого файла BES-1, 39 gEv, требуется скейлинг
    for(Int_t iEne=4; iEne<5; iEne++){    
       energyId = 6;
        for(Int_t pid=0; pid<3; pid++){  
            
            // charge > 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(0);
            drawOdj.back()->SetNameGraph(Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[0].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn1->Get( Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[0].Data()) ) );
            drawOdj.back()->NCQScaling(nq[pid],mass[pid]); // скейлинг точек ( (sqrt(pt^2+mass^2)-mass)/nq ; v2/nq )
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
            
            // текст легенды
            drawOdj.back()->SetLegendText(Form("#font[42]{ #scale[1.0]{%s, %s}}",particle[pid].Data(),MaskEnergyTxt_File1[iEne].Data()));
            
           // charge < 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(1);
            drawOdj.back()->SetNameGraph(Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[1].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn1->Get( Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[1].Data()) ) );
            drawOdj.back()->NCQScaling(nq[pid],mass[pid]); // скейлинг точек ( (sqrt(pt^2+mass^2)-mass)/nq ; v2/nq )
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
        }
    }

    // Точки из второго файла 54.4 GeV уже NCQ
    for(Int_t iEne=2; iEne<3; iEne++){   
      energyId = 7; 
        for(Int_t pid=0; pid<3; pid++){  
            fileIn2->cd();
            
            // charge > 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[6+iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(0);
            drawOdj.back()->SetNameGraph(Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[0].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn2->Get( Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[0].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()) ) );
            drawOdj.back()->SetLegendText(Form("#font[42]{ #scale[1.0]{%s, %s}}",particle[pid].Data(),MaskEnergyTxt_File2[iEne].Data()));
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
        
            // charge < 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[6+iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(1);
            drawOdj.back()->SetNameGraph(Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[1].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn2->Get( Form("fig4_%s %iGeV %s/Graph1D_y1",MaskChargeParticle_File2[1].Data(),MaskEnergy_File2[iEne],MaskParticle_File2[pid].Data()) ) );        
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
        }
    }

    // Точки из первого файла BES-1, 62 gEv, требуется скейлинг
    for(Int_t iEne=5; iEne<6; iEne++){    
        energyId = 8;
        for(Int_t pid=0; pid<3; pid++){  
            
            // charge > 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(0);
            drawOdj.back()->SetNameGraph(Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[0].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn1->Get( Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[0].Data()) ) );
            drawOdj.back()->NCQScaling(nq[pid],mass[pid]); // скейлинг точек ( (sqrt(pt^2+mass^2)-mass)/nq ; v2/nq )
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
            
            // текст легенды
            drawOdj.back()->SetLegendText(Form("#font[42]{ #scale[1.0]{%s, %s}}",particle[pid].Data(),MaskEnergyTxt_File1[iEne].Data()));
            
           // charge < 0
            drawOdj.push_back(new MyDrawObject());
            drawOdj.back()->SetMarkerColor(color[iEne]);
            drawOdj.back()->SetMarkerStyle(style[pid]);
            drawOdj.back()->SetMarkerSize(size[pid]);
            drawOdj.back()->SetNumberPadDraw(1);
            drawOdj.back()->SetNameGraph(Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[1].Data()));
            drawOdj.back()->SetDrawOdject((TGraphErrors*)fileIn1->Get( Form("gr_GeV%i_v2_values_%s%s_10_40",MaskEnergy_File1[iEne],MaskParticle_File1[pid].Data(),MaskChargeParticle_File1[1].Data()) ) );
            drawOdj.back()->NCQScaling(nq[pid],mass[pid]); // скейлинг точек ( (sqrt(pt^2+mass^2)-mass)/nq ; v2/nq )
            drawOdj.back()->VnIntScaling(v2int[energyId]); 
        }
    }

    Draw_Picture_new *canvas = new Draw_Picture_new();
    canvas->SetTextInfo(Form("#font[42]{#scale[1.0]{ v_{2}/v_{2}^{int}/n_{q} }}"),"Y", 1,0.7,0.55,0.5,90.0);
    canvas->SetTextInfo(Form("#font[42]{#scale[1.0]{ (m_{T}-m_{0})/n_{q} (GeV/c^{2}) }}"),"X", 1,0.3,0.5,0.5,0.0);

    canvas->SetTextInfo(Form("#font[42]{ #scale[1.0]{Au+Au Collisions (10-40%%)}}"),"Pad", 0, 0.1, 0.89*AxisYmax, 0.05, 0.0);
    canvas->SetTextInfo(Form("#font[42]{ #scale[1.0]{Positive particles}}" ),"Pad", 0, 0.8, 0.05*AxisYmax, 0.05, 0.0);
    canvas->SetTextInfo(Form("#font[42]{ #scale[1.0]{Negative particles}}" ),"Pad", 1, 0.8, 0.05*AxisYmax, 0.05, 0.0);

    canvas->SetTLineOnPad(AxisXmin, 0., AxisXmax, 0., 1, 3, 7, 0);
    canvas->SetTLineOnPad(AxisXmin, 0., AxisXmax, 0., 1, 3, 7, 1);
    canvas->SetAxisToPad(AxisXmin, AxisXmax, 0.07, AxisYmin, AxisYmax, 0.07);
    canvas->SetLegendPar(0.02,0.4,0.96,0.96,3,2);

    TCanvas *result = canvas->CanvasNxM(600,600, 1, 3, drawOdj, 0.05);
    result->SaveAs(Form("./Picture_NCQVintv2_BES.png"));
    result->SaveAs(Form("./Picture_NCQVintv2_BES.pdf"));

    delete result;
    delete canvas;
    
    fileIn1->Close();
    fileIn2->Close();
}

void makeplotstyle(){
  
    TStyle *mystyle = new TStyle("PlottingInStyle", "Style for Summary Plots");
    mystyle->SetLineWidth(2);
    mystyle->SetPalette(1);
    mystyle->SetCanvasColor(10);
    mystyle->SetHistFillColor(10);
    mystyle->SetHistFillStyle(0);
    mystyle->SetOptTitle(0);
    mystyle->SetOptStat(0);
    mystyle->SetCanvasBorderMode(0);//removes the yellow frame around the canvas
    mystyle->SetPadLeftMargin(0.16);
    mystyle->SetPadBottomMargin(0.15);
    mystyle->SetPadTickX(2);
    mystyle->SetPadTickY(2);
    mystyle->SetAxisColor(1, "X");
    mystyle->SetAxisColor(1, "Y");
    mystyle->SetLabelColor(1, "X");
    mystyle->SetLabelColor(1, "Y");
    mystyle->SetTickLength(0.03, "X");
    mystyle->SetTickLength(0.03, "Y");
    mystyle->SetTitleXSize(0.05);
    mystyle->SetTitleYSize(0.05);
    mystyle->SetNdivisions(508, "X");
    mystyle->SetNdivisions(508, "Y");
    mystyle->SetTitleXOffset(1.2);
    mystyle->SetTitleYOffset(1.4);
    mystyle->SetLabelOffset(0.02, "X");
    mystyle->SetLabelOffset(0.02, "Y");
    mystyle->SetLabelSize(0.05, "X");
    mystyle->SetLabelSize(0.05, "Y");
    mystyle->SetEndErrorSize(8);
    //mystyle->SetGridx();

    TFile f("style.root", "RECREATE");
    f.cd();
    mystyle->Write();
    f.Close();
}
