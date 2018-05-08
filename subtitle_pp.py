# -*- coding: utf-8 -*-
"""
Created on Thu May  3 11:00:38 2018

@author: atpandey
"""
#%%


def process_transcript(fname):
    with open(fname) as ff:
        for line in ff:
            line=line.rstrip()
            if len(line) ==0 or len(line) <= 2:
                pass
            elif (line[2]==':'):
                pass
            else:
                print(line,end=' ')
        
#%%
fname='1 - 01 L Introduction And Overview - lang_en_vs1.srt'
#print("operating on",fname)
process_transcript(fname)

#%%
fname='2 - 04 L Model Vs Data Driven Approaches - lang_en_vs1.srt'
#print("operating on",fname)
process_transcript(fname)
#%%

fname='3 - 06 L Data Driven Example Trajectory Clustering - lang_en_vs1.srt'
process_transcript(fname)
#%%

fname='4 - 07 L TrajectoryClustering2 - Online Prediction - lang_en_vs1.srt'
process_transcript(fname)

#%%

fname='5 - 08 L ThinkingAboutModelBasedApproaches - lang_en_vs1.srt'
process_transcript(fname)

#%%

fname='6 - 11 L MultimodalEstimationApproaches - lang_en_vs1.srt'
process_transcript(fname)

#%%

fname='7 - 13 L Overview Of Hybrid Approaches - lang_en_vs1.srt'
process_transcript(fname)
#%%

fname='8 - 14 L IntroToNaiveBayes - lang_en_vs1.srt'
process_transcript(fname)
