import { useState, useEffect } from "react";
import axios from 'axios'

function Home() {
    const [submission, setSubmission] = useState();
    const [error, setError] = useState('');


    const handleSubmit = () => {
        if(submission['name'].slice(-4) != '.cpp') {
            setError('wrong file format')
            return
        }
        axios.post('/submit', {
            submission: submission
        },{
            headers: {
                'Content-Type': 'multipart/form-data'
            }
        })
        .then((res) => {
            setError('Done')
        })
        .catch((err) => {
            console.log(err)
        })
    };

    return (
        <div>
            <input onChange={(e)=>setSubmission(e.target.files[0])} name="submission" type="file"/>
            <br/>
            <button type="submit" onClick={handleSubmit}>Submit</button>
            <br/>
            {error}
        </div>
    );
}

export default Home;