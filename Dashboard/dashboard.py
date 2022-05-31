from dash import Dash, dash_table,html
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
            html.H3(['Users statistics.'],style={'text-align':'center'}),
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
            dcc.Graph(id='host_graph', style={"width":"33.33%"}),
            dcc.Graph(id='user_graph', style={"width":"33.33%"}),
            dcc.Graph(id='traveler_graph', style={"width":"33.33%"})
            ],style={"display":"flex","margin-top":'-20px'}),
       
        html.Div([
            dash_table.DataTable(udf.usersStatistics.to_dict('records'), [{"name": i, "id": i} for i in udf.usersStatistics.columns]),
            ]),
        html.H4('Number of places per host.'),
    html.Div([
            dcc.RadioItems(
                id='xaxis_rad',
                options=[
                         {'label': 'Host', 'value': 'host'}
                ],
                value='host',
            ),
        ],style={"display":"none"}),

        html.Div([
            dcc.RadioItems(
                id='yaxis_rad',
                options=[{'label': 'Number of places', 'value': 'noOfPlaces'},],
                value='noOfPlaces',
            ),
        ],style={"display":"none"}),
    html.Div([
        dcc.Graph(id='the_graphh')
    ]),
    html.H3(['Places statistics.'],style={'text-align':'center'}),
    
    dcc.Dropdown(
        id="places_dropdown",
        options=[
            {'label':'Payment method','value':'method'},
            {'label':'Country','value':'country'},
            {'label':'Type','value':'room'}
            ],
        value='method',
        multi=False,
        clearable=False,
        ),
    
    html.Div([
        dcc.Graph(id='places_graph')
        ]),
    
    html.Div([
        dash_table.DataTable(pdf.placeStatistics.to_dict('records'), [{"name": i, "id": i} for i in pdf.placeStatistics.columns]),
        ]),
    
        html.H4('Duration per place.'),
    html.Div([
            dcc.RadioItems(
                id='xaxis',
                options=[
                         {'label': 'Duration', 'value': 'duration'}
                ],
                value='duration',
            ),
        ],style={"display":"none"}),

        html.Div([
            dcc.RadioItems(
                id='yaxis',
                options=[{'label': 'ID', 'value': 'id'},],
                value='id',
            ),
        ],style={"display":"none"}),
    html.Div([
        dcc.Graph(id='the_graphhh')
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
    Output(component_id='the_graphh', component_property='figure'),
    [Input(component_id='xaxis_rad', component_property='value'),
     Input(component_id='yaxis_rad', component_property='value')]
)
def update_graph(x_axis, y_axis):
    dff = pdf.hostPlacesDf
    barchart=px.bar(
            data_frame=dff,
            x=x_axis,
            y=y_axis,
            title=y_axis+': by '+x_axis,
            )
    barchart.update_layout(xaxis={'categoryorder':'total ascending'},
                           title={'xanchor':'center', 'yanchor': 'top', 'y':0.9,'x':0.5,})
    return (barchart)

@app.callback(
    Output(component_id='places_graph',component_property='figure'),
    [Input(component_id="places_dropdown",component_property='value')]
    )
def update_graph(attribute_dropdown):
    df=pdf.PlaceDf
    piechart=px.pie(data_frame=df,names=attribute_dropdown,hole=0)
    return piechart

@app.callback(
    Output(component_id='the_graphhh', component_property='figure'),
    [Input(component_id='xaxis', component_property='value'),
     Input(component_id='yaxis', component_property='value')]
)
def update_graph(x_axis, y_axis):
    dff = pdf.PlaceDf
    barchart=px.bar(
            data_frame=dff,
            x=y_axis,
            y=x_axis,
            title=y_axis+': by '+x_axis,
            )
    barchart.update_layout(xaxis={'categoryorder':'total ascending'},
                           title={'xanchor':'center', 'yanchor': 'top', 'y':0.9,'x':0.5,})
    return (barchart)


app.run_server(debug=False,port=3024)
