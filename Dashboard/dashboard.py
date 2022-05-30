import os
import pandas as pd
import numpy as np
import dash 
from dash import Dash, dash_table
import plotly.graph_objects as go
import dash_html_components as html
import dash_core_components as dcc
import hostDf as hdf
import travelerDf as tdf
import userDf as udf
import placeDf as pdf
from dash import Dash, dcc, html, Input, Output
import plotly.express as px

app = Dash(__name__)

app.layout=html.Div([
    html.Div([
        html.Div([
            html.H3(['Users statistics.'],style={'text-align':'center'})
            ],style={"margin-top":'20px'}),
        html.Label(['Variety among different types of users.'],style={'text-align':'center'}),
        dcc.Dropdown(
            id="attribute_dropdown",
            options=[
                {'label':'Age','value':'age_group'},
                {'label':'Gender','value':'gender'},
                {'label':'Nationality','value':'nationality'},
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
       
        html.Div([
            dash_table.DataTable(udf.usersStatistics.to_dict('records'), [{"name": i, "id": i} for i in udf.usersStatistics.columns]),
            ]),
        html.H4('Number of places per host.'),
    html.Div([
            # html.Label(['X-axis categories to compare:'],style={'font-weight': 'bold'}),
            dcc.RadioItems(
                id='xaxis_raditem',
                options=[
                         {'label': 'Host', 'value': 'host'}
                ],
                value='host',
            ),
        ]),

        html.Div([
            html.Br(),
            # html.Label(['Y-axis values to compare:'], style={'font-weight': 'bold'}),
            dcc.RadioItems(
                id='yaxis_raditem',
                options=[{'label': 'Number of places', 'value': 'noOfPlaces'},],
                value='noOfPlaces',
            ),
        ]),
    html.Div([
        dcc.Graph(id='the_graph')
    ]),
    ],style={"padding":"0% 7%","background-color":"floralwhite"}),
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

@app.callback(
    Output(component_id='the_graph', component_property='figure'),
    [Input(component_id='xaxis_raditem', component_property='value'),
     Input(component_id='yaxis_raditem', component_property='value')]
)
def update_graph(x_axis, y_axis):
    dff = pdf.hostPlaces
    barchart=px.bar(
            data_frame=dff,
            x=x_axis,
            y=y_axis,
            title=y_axis+': by '+x_axis,
            )
    barchart.update_layout(xaxis={'categoryorder':'total ascending'},
                           title={'xanchor':'center', 'yanchor': 'top', 'y':0.9,'x':0.5,})
    return (barchart)


app.run_server(debug=False,port=3024)
            # dash_table.DataTable(udf.UserDf.to_dict('records'), [{"name": i, "id": i} for i in udf.UserDf.columns]),