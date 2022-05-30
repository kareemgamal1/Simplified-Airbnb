import os
import pandas as pd
import numpy as np
import dash
import dash_html_components as html
import plotly.graph_objects as go
import dash_core_components as dcc
import hostDf as hdf
import travelerDf as tdf
import userDf as udf
from dash import Dash, dcc, html, Input, Output
import plotly.express as px

app = Dash(__name__)

app.layout=html.Div([
    html.Div([
        html.Label(['Variety among different types of users.'],style={'text-align':'center'}),
        dcc.Dropdown(
            id="attribute_dropdown",
            options=[
                {'Label':'Age','value':'age'},
                {'label':'Gender','value':'gender'},
                {'label':'Nationality','value':'nationality'},
                {'label':'Gender','value':'gender'},
                {'label':'Gender','value':'gender'},
                {'label':'Gender','value':'gender'},
                {'label':'Gender','value':'gender'},
                {'label':'Gender','value':'gender'},
                {'Label':'Age','value':'lname'}
                ],
            value='gender',
            multi=False,
            clearable=False,
            ),
        html.Div([
            html.Div([("Hosts")],style={"width":"33%","text-align":"center","z-index":"2"}),
            html.Div([("Users")],style={"width":"33%","text-align":"center","z-index":"2"}),
            html.Div([("Travelers")],style={"width":"33%","text-align":"center","z-index":"2"})
            ],style={"display":"flex","margin-top":'15px'}),
        html.Div([
            dcc.Graph(id='host_graph', style={"width":"33%"}),
            dcc.Graph(id='user_graph', style={"width":"33%"}),
            dcc.Graph(id='traveler_graph', style={"width":"33%"})
            ],style={"display":"flex","margin-top":'-20px'}),
    ],style={"padding":"0% 7%","background-color":"floralwhite"})
])

@app.callback(
    Output(component_id='host_graph',component_property='figure'),
    [Input(component_id="attribute_dropdown",component_property='value')]
    )

def update_graph(attribute_dropdown):
    df=hdf.HostDf
    piechart=px.pie(data_frame=df,names=attribute_dropdown,hole=0)
    return piechart

@app.callback(
    Output(component_id='traveler_graph',component_property='figure'),
    [Input(component_id="attribute_dropdown",component_property='value')]
    )
def update_graph(attribute_dropdown):
    df=tdf.TravelerDf
    piechart=px.pie(data_frame=df,names=attribute_dropdown,hole=0)
    return piechart

@app.callback(
    Output(component_id='user_graph',component_property='figure'),
    [Input(component_id="attribute_dropdown",component_property='value')]
    )
def update_graph(attribute_dropdown):
    df=udf.UserDf
    piechart=px.pie(data_frame=df,names=attribute_dropdown,hole=0)
    return piechart


app.run_server(debug=False,port=3024)

